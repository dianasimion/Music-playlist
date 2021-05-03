# Copyright 2020 Simion Diana-Maria 311CA

CC=gcc
CFLAGS=-Wall -Wextra -std=c99
DEBUG=-g -ggdb

build: tema1

tema1: playlist.o data.o show.o delete.o add.o
	$(CC) $(CFLAGS) $(DEBUG) playlist.o data.o show.o delete.o add.o -o tema1

playlist.o: playlist.c
	$(CC) $(CFLAGS) $(DEBUG) ./playlist.c -c -o playlist.o
	
data.o: data.c
	$(CC) $(CFLAGS) $(DEBUG) ./data.c -c -o data.o
	
show.o: show.c
	$(CC) $(CFLAGS) $(DEBUG) ./show.c -c -o show.o

delete.o: delete.c
	$(CC) $(CFLAGS) $(DEBUG) ./delete.c -c -o delete.o

add.o: add.c
	$(CC) $(CFLAGS) $(DEBUG) ./add.c -c -o add.o

clean:
	rm *.o tema1
