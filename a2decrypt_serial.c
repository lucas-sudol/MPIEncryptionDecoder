#include "a2.h"

void usage()
{
	fprintf(stderr, "Error!!\n \tTo run program: ./a2decrypt_serial (cipher txt file) (system dictionary txt file)\n");
}

int main(int argc, char **argv) { 
     //local main variables
    FILE* cyptherFp = NULL;
    FILE* dictFp = NULL;

    if(argc != 3){ //Incorrect number of arguments
        usage();
        return 0;
    }
    else {
        //Open file pointers
        cyptherFp = fopen(argv[1], "r");
        dictFp = fopen(argv[2], "r");

        if(cyptherFp == NULL || dictFp == NULL){
            fprintf(stderr, "Error opening files!\n");
            usage();
            return 0;
        }
    }
    //Get length of string in file
    fseek(cyptherFp, 0, SEEK_END);
    char encryptedString [ftell(cyptherFp) + 1];
    encryptedString[ftell(cyptherFp)] = '\0';
    fseek(cyptherFp, 0, SEEK_SET);

    //Save string from file
    fgets(encryptedString, sizeof(encryptedString), cyptherFp);
    fprintf(stdout, "input string: %s \n", encryptedString);

    //Find Unique letters
    char inputDictionary[strlen(encryptedString) + 1];
    uniqueLetters(encryptedString, inputDictionary);
    fprintf(stdout, "list of letters in the string: %s  (%ld unique characters)\n\n", inputDictionary, strlen(inputDictionary));

    // Create Trie
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
    
    //Call function to traverse permutations
    char * newDict = strdup(inputDictionary);

    //Generic call to calculate MPI permutations
    char results [MAXRESULT];
    results[0] = '\0';

    permuteRec_MPI(newDict, 0, strlen(inputDictionary), inputDictionary, encryptedString, parent, results);

    fprintf(stdout, "\tResults\n");
    if(strlen(results) > 0)
        fprintf(stdout, "%s",results);

    free(newDict);
    free(buffer);
    trie_free(parent);
    fclose(cyptherFp);
    fclose(dictFp);
    return 0;
}
