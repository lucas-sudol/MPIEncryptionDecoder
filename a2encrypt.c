#include "a2.h"

#define FILENAME "ciphertext.txt"

void usage()
{
	fprintf(stderr, "Error!! Incorrect command line arguments! \n \tTo run program: ./a2encrypt \"(input string)\"\n");
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

    //Find Unique letters
    uniqueLetters(argv[1], inputDictionary);
    printf("unique letters:\n %s, %ld\n", inputDictionary, strlen(inputDictionary));

    //Initialize empty encryption dictionary
    char encryptionDictionary[strlen(inputDictionary) + 1];
    memset(encryptionDictionary, '\0', sizeof(encryptionDictionary)); //Initialize as empty

    //Randomize encryption dictionary
    randomize(inputDictionary, encryptionDictionary);
    printf("encryption dictionary:\n %s, %ld\n", encryptionDictionary, strlen(encryptionDictionary));

    //Encrypt string
    encryptString(inputDictionary, encryptionDictionary, encryptionString);
    printf("Encrypted string: %s\n", encryptionString);

     FILE* fp = fopen(FILENAME, "w");
     fprintf(fp, encryptionString);
     fclose(fp);
    
    return 0;
}