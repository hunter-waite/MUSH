#include "mush.h"

int main(int argc, char *argv[]){
    int i, check;
    int count = 0;
    char line[LINESIZE];
    stage stages[NUMCMD];
    sigset_t mask;
   /* while(1) */{
        printf("here\n");
        get_line(line,LINESIZE);
        if(!strcmp(line,"exit")){
            return 0;
        }
        if(!strcmp(line,"clear")){
            printf("\e[1;1H\e[2J");
           /*  continue; */
        }
        count = get_stages(line,stages);
        parse_stages(stages,count);
        if(!strcmp(stages[0].argv[0], "cd")){
            if((check = chdir(stages[0].argv[1])) == -1){
                perror(stages[0].argv[1]);
               /* continue;*/
            }
        }
        
        sigemptyset(&mask);
        sigaddset(&mask,SIGINT);
        sigprocmask(SIG_BLOCK,&mask,NULL);
        launch_pipe(count,stages, mask);
        memset(stages,0,count * sizeof(stage));
    }
    return 0;
}

void launch_pipe(int count,stage *stages, sigset_t mask){
    /*create pipes then fork children to have copies of pipe list*/
    int i, j, check,rfd, wfd, status;
    int max_pipes = (count-1);
    int fd[18];
    int ind = 0;
    pid_t cpids[10];
    memset(cpids, 0, 10);
    for(i=0;i<max_pipes;i++){
        ind = i*2;
        if((check = pipe(fd+ind)) == -1){
            perror("pipe");
            continue;
        }
    }


    /*from here we need to fork and execute*/
    for(j=0;j<count;j++){
        if((cpids[j] = fork())){ /* this is the parent */
            if(cpids[j] == -1){
                perror("fork");
                break;
            }

        } else { /* this is the child */
            int pipe_write = (j*2) + 1;
            int pipe_read = (j*2) - 2;
            void* args[11];
            int i;
            printf("try");
            memset(args, 0, 11);
            printf("try");
            for(i=0;i<10;i++){
                strcpy(args[i], stages[j].argv[i]);
            }
    
            printf("stages in: %s\n",stages[j].out);
            printf("this is j: %d\n",j);

            /*set up pipes*/
            if(j == 0){
                if(stages[j].in[0] != '\0'){
                    if((rfd = open(stages[j].in, O_RDONLY)) == -1){
                        perror("open fd");
                        printf("PID: %d", getpid());
                        break;
                    }
                    dup2(rfd, STDIN_FILENO);
                    close(rfd);
                }
                if(count > 1){
                    dup2(fd[pipe_write], STDOUT_FILENO);
                    close_fd(fd); /*close all file descriptors??*/
                }
            }
            if(j == count-1){
                if(stages[j].out[0] != '\0'){
                    if((wfd = open(stages[j].out,
                                    O_WRONLY | O_CREAT | O_TRUNC))){
                        perror("open");
                        printf("PID: %d", getpid());
                        break;
                    }
                    dup2(wfd, STDOUT_FILENO);
                    close(wfd);
                }
                if(count > 1){
                    dup2(fd[pipe_read], STDIN_FILENO);
                    close_fd(fd);
                }
            }
            if(j != 0 && j != count-1){
                dup2(fd[pipe_read], STDOUT_FILENO);
                dup2(fd[pipe_write], STDIN_FILENO);
                /*close all?*/
                close_fd(fd);
            }
            /*unblock SIGINT*/
            sigprocmask(SIG_UNBLOCK,&mask,NULL);
            /*once the pipe has been set up then execute*/
            printf("stages argument: %s PID: %d\n",stages[j].argv[0],getpid());
            execvp(stages[j].argv[0],(char * const *)args);
            perror("exec");
            exit(3);
        }
    }
    /*close all file descriptors in parent*/
   /* close_fd(fd);*/

    /*wait for children to finish*/
    for(j=0;j<count;j++){
        /*flush stdout because buffered write*/
        printf("PID of the wait %d\n", cpids[j]);
        waitpid(cpids[j], &status, 0);
       /*need to check status and see how wait exited*/ 
    }
    
}

void close_fd(int fd[]){
    int i;
    for(i=0;i<18;i++){
        close(fd[i]);
    }
}
