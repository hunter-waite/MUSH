#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "parseline.h"
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void launch_pipe(int count,stage *stages, sigset_t mask);
void close_fd(int fd[]);
