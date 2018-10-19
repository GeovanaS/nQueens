CC=gcc

CFLAGS=-Wall -Wextra -Werror -O0 -g -std=c11 -pthread
LDFLAGS=-lm

.PHONY: all

all: teste_aluno grade 

aluno.o: aluno.c	

aluno: nqueenst.o aluno.o
	$(CC) $(CFLAGS) nqueenst.o aluno.o -lm -o aluno $(LDFLAGS)

nqueenst.o: nqueens.h nqueenst.c 
	$(CC) $(CFLAGS) -c nqueenst.c

test: nqueenst.o test.c
	$(CC) $(CFLAGS) -o test nqueenst.o test.c $(LDFLAGS) 

teste_aluno: aluno
	./aluno

grade: test
	./test

clean:
	rm -rf *.o aluno  test
