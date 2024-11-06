#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

void usage()
{
	fprintf(stderr, "Error!! Incorrect command line arguments! \n \tTo run program: ./a2encrypt \"(input string)\"\n");
}

void uniqueLetters (char* string, char* uniqueArray) {
    int letterCount = 0;
    int found;

    for(int i = 0; i < strlen(string); i++) {
        found = 0;
        for(int j = 0; j < letterCount; j++) {
            //Check uniqueArray
            if(tolower(string[i]) == uniqueArray[j])
                found = 1;
        }

        if(!found && tolower(string[i]) > 60 && tolower(string[i]) < 123) //check only for characters
            uniqueArray[letterCount++] = tolower(string[i]);
    }

    uniqueArray[letterCount] = '\0';
}

void randomize(char * uniqueArray, char *outputArray) {
    int count = 0;
    int random = 0;

    srand(time(0)); //Use time as seed
    while(count < strlen(uniqueArray)) {

        random =  rand() % ((int) strlen(uniqueArray));

        if(outputArray[random] == '\0') {
            outputArray[random] = uniqueArray[count++];
        }
    }
}

void encryptString(char * inputDict, char* encryptionDict,  char *encryptionString) {
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

int main(int argc, char **argv) { 
    if(argc != 2){ //Incorrect number of arguments
        usage();
        return 0;
    }
    else { //Empty string
        if(strlen(argv[1]) == 0) {
            fprintf(stderr,"Error!! Ensure passed string is not empty!\n\n");
            usage();
            return 0;
        }
    }

    //Declare variables
    char inputDictionary[strlen(argv[1]) + 1];
    char encryptionString[strlen(argv[1]) + 1];
    strcpy(encryptionString, argv[1]);

    uniqueLetters(argv[1], inputDictionary);
    printf("unique letters:\n %s, %ld\n", inputDictionary, strlen(inputDictionary));

    //Initialize empty encryption dictionary
    char encryptionDictionary[strlen(inputDictionary) + 1];
    memset(encryptionDictionary, '\0', sizeof(encryptionDictionary));

    //Set empty dictionary
    randomize(inputDictionary, encryptionDictionary);

    printf("encryption dictionary:\n %s, %ld\n", encryptionDictionary, strlen(encryptionDictionary));



    encryptString(inputDictionary, encryptionDictionary, encryptionString);

    printf("Encrypted string: %s\n", encryptionString);
    
    return 0;
}