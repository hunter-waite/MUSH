#include "parseline.h"

int main(int argc, char *argv[]){
    char line[LINESIZE];
    stage stages[NUMCMD];
    get_line(line,LINESIZE);
    return 0;
}

void get_line(char *line,int size){
    printf("line: ");
    if(!fgets(line,size,stdin)){
        perror("getline");
        exit(EXIT_FAILURE);
    }
}
