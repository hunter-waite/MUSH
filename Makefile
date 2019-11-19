CFLAGS = -g -ansi -Wall -Wextra -pedantic
CC = gcc
LD = gcc


all: parseline

parseline: parseline.o
	$(LD) -o parseline parseline.o

parseline.o: parseline.c parseline.h
	$(CC) $(CFLAGS) -c -o parseline.o parseline.c

clean:
	rm -f *.o
