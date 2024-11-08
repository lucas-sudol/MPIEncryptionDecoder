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

int permutations(char* array, int n, char* permutation, int index, char* inputDict, char* finalString) {
    char* newArr;
    char* newPermutation;
    char* finalStringDecrypted;
    int count = 0;

    //Base Case - check if combination array is empty
    if(n < 1){
        //Print permutation and free resources
        fprintf(stderr, "Key: %s\n", permutation);

        finalStringDecrypted = strdup(finalString);
        encryptString(inputDict, permutation, finalStringDecrypted);
        fprintf(stderr, "Decrypted: %s\n", finalStringDecrypted);

        free(finalStringDecrypted);
        free(array);
        free(permutation);
        return 1;
    }

    //Create branches of characters in array
    else {
        for(int i = 0; i < strlen(array); i++){
            //Check for empty characters
            if(array[i] != -1) {
                //Create new array with current character missing
                newArr = strdup(array);
                newArr[i] = -1;

                //Add character to new permutation
                newPermutation = strdup(permutation);
                newPermutation[index] = array[i];

                //Recursively call permutations and store count
                count += permutations(newArr, n-1, newPermutation, index + 1, inputDict, finalString);
            }
        }
    }

    //Free resources and return count
    free(array);
    free(permutation);
    return count;
}
