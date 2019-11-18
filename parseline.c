#include "parseline.h"

int main(int argc, char *argv[]){
    char line[LINESIZE];
    stage stages[NUMCMD];
    get_line(line,LINESIZE);
    return 0;
}


/*the way I'm thinking we do this is to have the acutal parse function return
 * an int that we can pass to a function that either prints a corresponding
 * error message, just because there are so many. Otherwise we can just return
 * 0 and print the stages. I'm super open to doing other ways.*/

void get_line(char *line,int size){
    printf("line: ");
    if(!fgets(line,size,stdin)){
        perror("getline");
        exit(EXIT_FAILURE);
    }
}

void print_stage(const struct stage s){
    int i;
    
    printf("--------\n");
    printf("Stage %d: \"%s\"\n", s.snum, s.input);
    printf("--------\n");
    printf("%12s", "input: \0"); /*have to add actual input*/
    printf("%12s", "output: \0"); /*add actual output*/
    printf("%12s%d\n", "argc: \0", s.argcount);
    printf("%12s", "argv: \0");
    for(i = 0; i < s.argcount; i++){
        printf("\"%s\", ", s.argv[i]);
    }
    printf("\n\n");
 
}
