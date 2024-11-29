#include "func.h"

#define FILENAME "ciphertext.txt"

void usage()
{
	fprintf(stderr, "Error!! Incorrect command line arguments! \n \tTo run program: ./encrypt \"(input string)\"\n");
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

    printf("input string: %s\n\n", encryptionString);

    //Find Unique letters
    uniqueLetters(argv[1], inputDictionary);
    printf("input dictionary: %s (%ld unique characters)\n", inputDictionary, strlen(inputDictionary));

    //Initialize empty encryption dictionary
    char encryptionDictionary[strlen(inputDictionary) + 1];
    memset(encryptionDictionary, '\0', sizeof(encryptionDictionary)); //Initialize as empty

    //Randomize encryption dictionary
    randomize(inputDictionary, encryptionDictionary);
    printf("encryption dictionary: %s\n\n", encryptionDictionary);

    //Encrypt string
    encryptString(inputDictionary, encryptionDictionary, encryptionString);
    printf("encrypted string: %s\n\n", encryptionString);

    //Write to file
    FILE* fp = fopen(FILENAME, "w");
    fprintf(fp, encryptionString);
    fclose(fp);
    
    return 0;
}