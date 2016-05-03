CC=gcc
CFLAGS=-lm -O2 -Wall -Wextra

main: main.c main.h draw.c flag.c
	gcc ${CFLAGS} *.c -o flagger
