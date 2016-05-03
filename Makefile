CC=gcc
CFLAGS=-lm -O2

main: main.c main.h draw.c flag.c
	gcc ${CFLAGS} *.c -o main
