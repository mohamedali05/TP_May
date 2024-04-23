CC = gcc
CFLAGS = -lm -Wall 

.PHONY: all clean

default: all

all: main

main: main.c tp3.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f main
