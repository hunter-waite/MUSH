#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "parseline.h"
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>

void launch_pipe(int count,stage *stages);
void close_fd(int fd[]);
