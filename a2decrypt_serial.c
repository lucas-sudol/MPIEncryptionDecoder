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
    fseek(cyptherFp, 0, SEEK_END);
    char encryptedString [ftell(cyptherFp) + 1];
    encryptedString[ftell(cyptherFp)] = '\0';
    fseek(cyptherFp, 0, SEEK_SET);

    fgets(encryptedString, sizeof(encryptedString), cyptherFp);
    fprintf(stderr, "%s \n", encryptedString);

    char inputDictionary[strlen(encryptedString) + 1];
    //Find Unique letters
    uniqueLetters(encryptedString, inputDictionary);
    fprintf(stderr, "%s \n", inputDictionary);
    fprintf(stderr, "%ld\n", strlen(inputDictionary));


    fprintf(stderr, "Permutation count is %d\n", permutations(strdup(inputDictionary), strlen(inputDictionary), strdup(inputDictionary), 0, inputDictionary, encryptedString));





    fclose(cyptherFp);
    fclose(dictFp);
    return 0;
}
