#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "trie.h"

#define MAXLINE 256
#define MAXRESULT 10000


void uniqueLetters (char*, char*);
void randomize(char *, char *);
void encryptString(char *, char*,  char*);
char* strdup(char *); 
int checkDictionary(char *, struct trie * parent);
void decrypt_MPI(char* dict, char * encryptedString, int num_threads, int thread_id, char* results);
void permuteRec_MPI(char* str, int idx, int n, char * dict, char * finalString , struct trie * parent, char* results);