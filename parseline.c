#include "parseline.h"

int main(int argc, char *argv[]){
    int count, i;
    char line[LINESIZE];
    stage stages[NUMCMD];
    get_line(line,LINESIZE);
    count = get_stages(line,stages);
    return 0;
}

/*the way I'm thinking we do this is to have the acutal parse function return
 * an int that we can pass to a function that either prints a corresponding
 * error message, just because there are so many. Otherwise we can just return
 * 0 and print the stages. I'm super open to doing other ways.*/


int get_stages(char *line, stage *stages){
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
        printf("Token: '%s'\n",token);
        stages[count].snum = count;
        strcpy(stages[count].input, token);
        token = strtok(NULL,"|");
        count ++;
    }
    return count;
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
    }
    else if(line[size-1] == '\n')    /* checks for full line case */
        line[size-1] = '\0';
    else if(line[strlen(line)-1])   /* last character to null if newline */
        line[strlen(line)-1] = '\0';
    if(line[strlen(line)-1] == '|'){
        fprintf(stderr, "invalid null command\n");
        exit(8); 
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

int check_whitespace(char *s){
    int i;
    for(i = 0; i < (int)strlen(s); i++){
        if(!isspace(s[i]))
            return 1;
    }
    return 0;
}

void parse_stages(stage *s, int index){
    int i, incount, outcount, words;
    char copy[LINESIZE];
    char **breakdown[LINESIZE];
    for(i=0; i < index; i++){
        memset(copy, 0, LINESIZE);
        strcpy(copy, s[i].input);

        if(!check_whitespace(s[i].input)){
            fprintf(stderr, "invalid null command\n");
            exit(4);
        }
        /*seperate the input into parts to work with*/
        words = word_count(s[i].input);
        *breakdown = calloc(words, sizeof(char));
        
        
/*
        if(i==0 && (count - 1) != 0){
        
        }
        else if(i == (count - 1)){

        }
*/
    }
}

int word_count(char *s){
    int i, count;
    count = 0;
    for(i=0;s[i] != '\0';i++){
        if(s[i] == ' ' && s[i+1] != ' '){
            count++;
        }
    }
    return count;
}
