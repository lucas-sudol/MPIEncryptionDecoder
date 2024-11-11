#include "a2.h"

//Find unique letters in string and store to array
void uniqueLetters (char* string, char* uniqueArray) {
    int letterCount = 0;
    int found;

    for(int i = 0; i < strlen(string); i++) {
        found = 0;
        for(int j = 0; j < letterCount; j++) {
            //Check uniqueArray
            if(tolower(string[i]) == uniqueArray[j]){
                found = 1;
                j = letterCount;
            }
        }

        if(!found && isalpha(string[i])) //check only for characters
            uniqueArray[letterCount++] = tolower(string[i]);
    }

    uniqueArray[letterCount] = '\0';
}

//Randomize unique letter array to and store in output array
void randomize(char * uniqueArray, char *outputArray) {
    int count = 0;
    int random = 0;

    srand(time(NULL)); //Use time as seed
    while(count < strlen(uniqueArray)) {
        random =  rand() % ((int) strlen(uniqueArray));

        if(outputArray[random] == '\0') {
            outputArray[random] = uniqueArray[count++];
        }
    }
}

//Using original string, replace letter with encrypted dictionary
void encryptString(char * inputDict, char* encryptionDict,  char* encryptionString) {
    for(int i = 0; i < strlen(encryptionString); i++)
    {
        for(int j = 0; j < strlen(inputDict); j++){
            if(tolower(encryptionString[i]) == inputDict[j]){
                encryptionString[i] = encryptionDict[j];
                j = strlen(inputDict);
            }
        }
    }
}

char* strdup(char * old) {
    char * newString = malloc(sizeof(char) * (strlen(old) + 1));
    strcpy(newString, old);
    newString[strlen(old)] = '\0';
    return newString;
}

int checkDictionary(char *string, struct trie * parent) {
    char * token = strtok(string, " ?:;.,!\0");
    while(token != NULL){
        //Check trie if word exists in dictionary
        if(!((long int) (trie_search(parent, token)))) {
            return 0; //If it doesnt, exit spell checker
        }
        token = strtok(NULL, " ?:;.,!\0"); //Fetch next word
    }

    return 1; //Passed spellcheck
}


//Modified permutation algorithm cited from https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/

// Function to print permutations of the string
// This function takes two parameters:
// 1. String
// 2. Starting index of the string.
void permuteRec(char* str, int idx, int n, char * dict, char * finalString , struct trie * parent) {
    // Base case
    if (idx == n - 1) {
        char * finalStringDecrypted = strdup(finalString);
        encryptString(dict, str, finalStringDecrypted); //Find possible string with permutation
        char* nontokenizedString = strdup(finalStringDecrypted); //Save copy (strtok destroys string)


        if(checkDictionary(finalStringDecrypted, parent)) {
            //Print decrypted string
           fprintf(stderr, "Decrypted string: %s\n", nontokenizedString); 
        }

        free(finalStringDecrypted);
        free(nontokenizedString);
        return;
    }
    else {
        char temp;
        for (int i = idx; i < n; i++) {
            // Swapping
            temp = str[idx];
            str[idx] = str[i];
            str[i] = temp;

            // First idx+1 characters fixed
            permuteRec(str, idx + 1, n, dict, finalString, parent);

            // Backtrack
            str[i] = str[idx];
            str[idx] = temp;
        }
        return;
    }
}

void decrypt_MPI(char* dict, char * encryptedString, int num_threads, int thread_id, char* results) {
    FILE* dictFp = fopen(dict, "r");

    char inputDictionary[strlen(encryptedString) + 1];
    uniqueLetters(encryptedString, inputDictionary);

    struct trie * parent = trie_create();
    char * buffer = calloc(MAXLINE, 1);

    //Create trie dictionary
    while (fgets(buffer, MAXLINE, dictFp)) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Convert each character to lowercase
        for (int i = 0; buffer[i] != '\0'; i++) {
            buffer[i] = tolower(buffer[i]);
        }
            // Insert the word into the trie
        trie_insert(parent, buffer, (void *)1);
    }


    char temp;
    char * newDict;
    char* unique = strdup(inputDictionary); //Copy dictionary since it is being when dividing work
    int base_chunk_size = strlen(inputDictionary) / num_threads;  // Minimum number of tasks per thread
    int remainder = strlen(inputDictionary) % num_threads;         // Extra tasks to be distributed among threads

    // Starting index for the current thread (distribute extra tasks round-robin)
    int start_index = thread_id * base_chunk_size + (thread_id < remainder ? thread_id : remainder);

    // Ending index for the current thread
    int end_index = start_index + base_chunk_size + (thread_id < remainder ? 1 : 0);

    // Output the task (indexes) assigned to this thread
    for (int i = start_index; i < end_index; i++) {
        temp = inputDictionary[0];
        inputDictionary[0] = inputDictionary[i];
        inputDictionary[i] = temp;

        //Print off encrypted keys with different starting letters - splitting the workload by different permutation branches
        fprintf(stderr, "Rank %d: is %s\n", thread_id, inputDictionary);
        newDict = strdup(inputDictionary);
        permuteRec_MPI(newDict, 1, strlen(inputDictionary), unique, encryptedString, parent, results);

        // Backtrack
        inputDictionary[i] = inputDictionary[0];
        inputDictionary[0] = temp;
        free(newDict);
    }

    free(buffer);
    trie_free(parent);
    free(unique);
}


void permuteRec_MPI(char* str, int idx, int n, char * dict, char * finalString , struct trie * parent, char* results) {
    // Base case
    if (idx == n - 1) {
        char * finalStringDecrypted = strdup(finalString);
        encryptString(dict, str, finalStringDecrypted); //Find possible string with permutation
        char* nontokenizedString = strdup(finalStringDecrypted); //Save copy (strtok destroys string)


        if(checkDictionary(finalStringDecrypted, parent)) {
            //Print decrypted string
            strcat(results, nontokenizedString);
            strcat(results, "\n");
        }

        free(finalStringDecrypted);
        free(nontokenizedString);
        return;
    }
    else {
        char temp;
        for (int i = idx; i < n; i++) {
            // Swapping
            temp = str[idx];
            str[idx] = str[i];
            str[i] = temp;

            // First idx+1 characters fixed
            permuteRec_MPI(str, idx + 1, n, dict, finalString, parent, results);

            // Backtrack
            str[i] = str[idx];
            str[idx] = temp;
        }
        return;
    }
}
