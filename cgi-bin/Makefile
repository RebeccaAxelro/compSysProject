CC = gcc

CSAPP_INC = ../../../../include
CSAPP_SRC = ../../../../src

CFLAGS = -O2 -Wall -I ..

all: recipe

adder: recipe.c
	$(CC) $(CFLAGS) -o recipe recipe.c
 
clean:
	rm -f recipe *~
