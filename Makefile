CFLAGS = -g -ansi -Wall -pedantic
CC = gcc
LD = gcc


all: parseline

parseline: parseline.o
	$(LD) -o parseline parseline.o

parseline.o: parseline.c parseline.h
	$(CC) $(CLFAGS) -c -o parseline.o parseline.c

clean:
	rm -f *.o
