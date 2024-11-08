CC = gcc

CFLAGS = -Wall -g -std=c11 -O0
#SERIALFLAGS = -Wall -g -std=c11 -O0

all: a2encrypt a2decrypt_serial

#Encrypt String
a2encrypt: a2encrypt.c a2functions.o
	$(CC) $(CFLAGS) a2encrypt.c a2functions.o -o a2encrypt

#Serial decrypt version
a2decrypt_serial: a2decrypt_serial.c a2functions.o
	$(CC) $(CFLAGS) a2decrypt_serial.c a2functions.o -o a2decrypt_serial

#serial: serial.c $(CC) $(CFLAGS) serial.c -o serial

clean:  
	rm -f a2encrypt a2decrypt_serial ciphertext.txt a2functions.o

