#include "parseline.h"

int main(int argc, char *argv[]){
    char line[LINESIZE] = {'t','r','y',' ', '|'};
    stage stages[NUMCMD];
    /*get_line(line,LINESIZE);*/
    get_stages(line,stages);
    printf("stop");
    return 0;
}

/*the way I'm thinking we do this is to have the acutal parse function return
 * an int that we can pass to a function that either prints a corresponding
 * error message, just because there are so many. Otherwise we can just return
 * 0 and print the stages. I'm super open to doing other ways.*/


void get_stages(char *line, stage *stages){
    char *token = strtok(line,"|");
    int count = 0;
    if(!token){ /* null line case */
        fprintf(stderr,"invalid null command\n");
        exit(3);
    }
    while(token != NULL){
        if(count >= NUMCMD){
            fprintf(stderr,"pipeline too deep\n");
            exit(EXIT_FAILURE);
        }
        if(token[0] == ' ')
            token++;
        printf("Token: %s\n",token);
        populate_stage(stages[count], token, 100);
        /*function to parse through each token*/
        token = strtok(NULL,"|");
        count ++;
    }
}

/* gets the line from the prompt in the parseline 
 * max LINESIZE characters
 * if the last character is a newline changes it to a null */
void get_line(char *line,int size){
    printf("line: "); /* the prompt */
    if(!fgets(line,size,stdin)){
        perror("getline");
        exit(EXIT_FAILURE);
    }
    if(strchr(line, '\n') == NULL){ /* if the line is too long */
        fprintf(stderr,"command too long\n");
        exit(3);
    } else if(line[size-1] == '\n')    /* checks for full line case */
        line[size-1] = '\0';
    else if(line[strlen(line)-1])   /* last character to null if newline */
        line[strlen(line)-1] = '\0';
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

void populate_stage(stage st, char *token, int stnum){
    st.snum = stnum;
    strcpy(st.input, token);
}
