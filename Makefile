CFLAGS =  -Wall -Wextra -pedantic -ansi -O2
CC = gcc


sold: sold.c test.c
	$(CC) sold.c test.c -o sold $(CFLAGS)
