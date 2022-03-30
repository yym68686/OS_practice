#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
int main()
{
    int pid;    
    int fd[2];
    char buf[32];

    pipe(fd); 
    pid = fork();
    if (pid == 0) { 
        dup2(fd[1], 1); 
        close(fd[0]);
        close(fd[1]);
		int fd = open("test.c", O_RDONLY);
		char buf[111111];
		read(fd, buf, sizeof(buf));
		close(fd);
		write(1, buf, sizeof(buf));
        //execlp("cat", "cat", "/etc/passwd", NULL);
        exit(0);
    }
	//wait(NULL);
    dup2(fd[0], 0); 
    close(fd[0]);
    close(fd[1]);

    execlp("wc", "wc", "-l", NULL);
    return 0;
}
