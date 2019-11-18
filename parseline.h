#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define LINESIZE 512
#define NUMCMD 10
#define NUMARGS 10

typedef struct stage {
    int snum;
    char input[LINESIZE];
    int pipeto;
    int argcount;
    char argv[NUMARGS][LINESIZE];
} stage;

void get_line(char *line,int size);
