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
    char input[LINESIZE]; /*make sure to store this with no newline*/
    int pipeto;  /*could be NULL, if so find output*/
    char in[LINESIZE];
    char out[LINESIZE];
    int argcount;
    char argv[NUMARGS][LINESIZE];
    /*need some way to tell between inputs and outputs*/
} stage;

int get_stages(char *line, stage *stages);
void get_line(char *line,int size);
void print_stage(const struct stage s, int max);
void populate_stage(stage st, char *token, int stnum);
int check_whitespace(char *s);
void parse_stages(stage *s, int index);
void on_error(char *cmd, unsigned int error);
