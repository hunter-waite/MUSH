#include "parseline.h"

int main(int argc, char *argv[]){
    char line[LINESIZE];
    get_line(line,LINESIZE);
    printf(line);
    return 0;
}

void get_line(char *line,int size){
    printf("line: ");
    if(!fgets(line,size,stdin)){
        perror("getline");
        exit(EXIT_FAILURE);
    }
}
