#include "mush.h"
#include "parseline.h"

int main(int argc, char *argv[]){
    int i, check;
    int count = 0;
    char line[LINESIZE];
    stage stages[NUMCMD];
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    sigprocmask(SIG_BLOCK,&mask,NULL);
    while(1){
        get_line(line,LINESIZE);
        if(!strcmp(line,"exit")){
            return 0;
        }
        count = get_stages(line,stages);
        parse_stages(stages,count);
        if(!strcmp(stages[0].argv[0], "cd")){
            if((check = chdir(stages[0].argv[1])) == -1){
                perror(stages[0].argv[1]);
                continue;
            }
        }
        memset(stages,0,count * sizeof(stage));
    }
    return 0;
}
