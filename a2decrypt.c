#include "a2.h"
#include <mpi.h>     
#include <unistd.h>


void usage()
{
	fprintf(stderr, "Error!!\n \tTo run program: mpiexec -n (process count )./a2decrypt (cipher txt file) (system dictionary txt file)\n");
}

int main(int argc, char **argv) { 
    char       dict[MAXLINE];  /* Name of dictionary */
    char       encryptedString[MAXLINE]; /* Encrypted String */
    int        comm_sz;               /* Number of processes    */
    int        my_rank;               /* My process rank        */

    /* Start up MPI */
    MPI_Init(NULL, NULL); 

    /* Get the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

    /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

    if (my_rank != 0) { 
        char results [MAXRESULT];
        results[0] = '\0';

        //Receive dictionary name and string from main thread
        MPI_Recv(dict, MAXLINE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(encryptedString, MAXLINE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        //Call function to calculate permutations and save to results
        decrypt_MPI(dict, encryptedString, comm_sz, my_rank, results);

        //Send results to main
        MPI_Send(results, strlen(results) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

   } else {  
        //local main variables
        FILE* cyptherFp = NULL;
        FILE* dictFp = NULL;

        if(argc != 3){ //Incorrect number of arguments
            usage();
            MPI_Finalize(); 
            return 0;
        }
        else {
            //Open file pointers
            cyptherFp = fopen(argv[1], "r");
            dictFp = fopen(argv[2], "r");

            if(cyptherFp == NULL || dictFp == NULL){
                fprintf(stderr, "Error opening files!\n");
                usage();
                MPI_Finalize(); 
                return 0;
            }
        }

        //Save string from file
        fgets(encryptedString, MAXLINE, cyptherFp);
        fprintf(stdout, "input string to the MPI functions: %s \n", encryptedString);

        //Print unique letters
        char inputDictionary[strlen(encryptedString) + 1];
        uniqueLetters(encryptedString, inputDictionary);
        fprintf(stdout, "list of letters in the string: %s  (%ld unique characters)\n\n", inputDictionary, strlen(inputDictionary));
        
        for (int q = 1; q < comm_sz; q++) {
         /* Receive message from some process */
            MPI_Send(argv[2],  strlen(argv[2]) + 1, MPI_CHAR, q, 0, MPI_COMM_WORLD);
            MPI_Send(encryptedString, strlen(encryptedString) + 1, MPI_CHAR, q, 0, MPI_COMM_WORLD);
        }

        //Generic call to calculate MPI permutations
        char results [MAXRESULT];
        results[0] = '\0';
        decrypt_MPI(argv[2], encryptedString, comm_sz, my_rank, results);

        //Print results for main thread
        fprintf(stdout, "\tResults\n");
        if(strlen(results) > 0)
            fprintf(stdout, "Rank %d:\n%s", my_rank, results);

        //Collect results from other proccesses and print
        for (int q = 1; q < comm_sz; q++) {
            MPI_Recv(results,  MAXRESULT, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if(strlen(results) > 0)
                fprintf(stdout, "Rank %d:\n%s", q, results);
        }
        fclose(cyptherFp);
        fclose(dictFp);
   }

    MPI_Finalize(); 
    return 0;
}