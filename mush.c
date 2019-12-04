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
        launch_pipe(count);
        memset(stages,0,count * sizeof(stage));
    }
    return 0;
}


void launch_pipe(int count){
    /*create pipes then forl children to have copies of pipe list*/
    int i, check;
    int max_pipes = (count-1);
    int fd[18];
    int ind = 0;
    for(i=0;i<max_pipes;i++){
        if(i!=0){
            ind += 2;
        }
        else{
            ind = 0;
        }
        if((check = pipe(fd+ind)) == -1){
            perror("pipe");
            continue;
        }
    }
    /*from here we need to fork and execute*/
     
}
