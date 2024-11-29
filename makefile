CC = gcc
MPI = mpicc

CFLAGS = -Wall -g -std=c99 -O0

all: encrypt decrypt_serial decrypt

#Encrypt String
encrypt: encrypt.c functions.o trie.o func.h
	$(CC) $(CFLAGS) encrypt.c functions.o trie.o -o encrypt

#Serial decrypt version
decrypt_serial: decrypt_serial.c functions.o trie.o func.h
	$(CC) $(CFLAGS) decrypt_serial.c functions.o trie.o -o decrypt_serial

#Parallel version
decrypt: decrypt.c functions.o trie.o func.h
	$(MPI) $(CFLAGS) decrypt.c functions.o trie.o -o decrypt

clean:  
	rm -f encrypt decrypt_serial decrypt ciphertext.txt functions.o trie.o

