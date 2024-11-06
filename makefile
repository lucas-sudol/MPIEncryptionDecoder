CC = gcc

CFLAGS = -Wall -g -std=c11 -O0
SERIALFLAGS = -Wall -g -std=c11 -O0

all: a2encrypt

a2encrypt: a2encrypt.c
	$(CC) $(CFLAGS) a2encrypt.c -o a2encrypt

#serial: serial.c $(CC) $(CFLAGS) serial.c -o serial

clean:  
	rm -f a2encrypt

