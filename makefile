CC = gcc
MPI = mpicc

CFLAGS = -Wall -g -std=c99 -O0

all: a2encrypt a2decrypt_serial a2decrypt

#Encrypt String
a2encrypt: a2encrypt.c a2functions.o trie.o a2.h
	$(CC) $(CFLAGS) a2encrypt.c a2functions.o trie.o -o a2encrypt

#Serial decrypt version
a2decrypt_serial: a2decrypt_serial.c a2functions.o trie.o a2.h
	$(CC) $(CFLAGS) a2decrypt_serial.c a2functions.o trie.o -o a2decrypt_serial

#Parallel version
a2decrypt: a2decrypt.c a2functions.o trie.o a2.h
	$(MPI) $(CFLAGS) a2decrypt.c a2functions.o trie.o -o a2decrypt

clean:  
	rm -f a2encrypt a2decrypt_serial a2decrypt ciphertext.txt a2functions.o trie.o

