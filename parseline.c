#include "parseline.h"

/* in the parse stages we need to figure out the:
 *  argument count
 *  argument variables
 *  ambiguous input and output */

int main(int argc, char *argv[]){
    int count = 0;
    char line[LINESIZE];
    stage stages[NUMCMD];
    get_line(line,LINESIZE);
    count = get_stages(line,stages);
    parse_stages(stages,count);
    return 0;
}

int get_stages(char *line, stage *stages){
    char *token = strtok(line,"|");
    int count = 0;
    if(!token) /* null line case */
        on_error("",3);
    while(token != NULL){
        if(count >= NUMCMD)
            on_error("",1);
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
    memset(line,0, LINESIZE);
    printf("line: "); /* the prompt */
    if(!fgets(line,size,stdin)){
        perror("getline");
        exit(EXIT_FAILURE);
    }
    if(strchr(line, '\n') == NULL) /* if the line is too long */
        on_error("",0);
    else if(line[size-1] == '\n')    /* checks for full line case */
        line[size-1] = '\0';
    else if(line[strlen(line)-1])   /* last character to null if newline */
        line[strlen(line)-1] = '\0';
    if(line[strlen(line)-1] == '|')
        on_error("",3);
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

/* parses the stages to check for errors and to fill their respective
 * stage struct */
void parse_stages(stage *s, int index){
    int i;
    int incount = 0;
    int outcount = 0;
    char *old, *new, command[LINESIZE];
    for(i=0;i<index; i++){  /* loops through all the stages */
        if(!check_whitespace(s[i].input))   /* if a stage is empty */
            on_error("",3);
        s[i].argcount = 0;
        /* loops through all the "arguments" in the stage
         *  parses for redirection and such */
        new = strtok(s[i].input," ");
        strcpy(command,new);
        while(new != NULL){
            printf("New: %s\n",new); 
            old = new;
            new = strtok(NULL," ");

            if(old[0] == '<'){  /* input redirection */
                if(new){    /* correct redirection */
                    strncpy(s[i].in,new,LINESIZE);
                    if(++incount >= 2)
                        on_error(command,4);
                }
                else {  /* incorrect redirection */
                    on_error(command,4);
                }
            }
            else if(old[0] == '>'){  /* output redirect */
                if(new){    /* correct redirect */
                    strncpy(s[i].out,new,LINESIZE);
                    if(++outcount >= 2)
                        on_error(command,5);
                }
                else{   /* incorrect redirect */
                    on_error(command,5);
                }
            }
        }

        printf("Argc: %d\n",s[i].argcount);
    }
}

/* prints the correct error message to stderr and exits 
 * error    message
 * 0:       cmd too long
 * 1:       pipeline too dee
 * 2:       too many arguments
 * 3:       invalid null command
 * 2:       too many arguments
 * 3:       invalid null command
 * 4:       bad input redir
 * 5:       bad output redir
 * 6:       ambig input
 * 7:       ambig output */
void on_error(char *cmd, unsigned int error){
    if(error == 0){
        fprintf(stderr,"command too long\n");
    } else if(error == 1){
        fprintf(stderr,"pipeline too deep\n");
    } else if(error == 2){         
        fprintf(stderr,"%s: too many arguments\n",cmd);
    } else if(error == 3){         
        fprintf(stderr,"invalid null command\n");
    } else if(error == 4){         
        fprintf(stderr,"%s: bad input redirection\n",cmd);
    } else if(error == 5){         
        fprintf(stderr,"%s: bad output redirection\n",cmd);
    } else if(error == 6){         
        fprintf(stderr,"%s: ambiguous input\n",cmd);
    } else if(error == 7){         
        fprintf(stderr,"%s: ambiguous output\n",cmd);
    } else {
        fprintf(stderr,"undefined error: exiting\n");
    }
    exit(3);
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
