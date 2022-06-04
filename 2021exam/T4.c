#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    int pid;
    int fd[2];
    int file;

    char buf[22222];
    pipe(fd);
    pid=fork();
    if(pid == 0)
    {
        file = open("result.txt", O_CREAT | O_RDWR, 666);
        dup2(fd[0], 0);
        dup2(file, 1);
        close(fd[0]);
        close(fd[1]);
        close(file);
        execlp("wc", "wc", "-l", NULL);
        printf("%s",buf);
    }

    file = open("/etc/passwd", O_RDONLY);
    dup2(file, 0);
    dup2(fd[1], 1);
    close(fd[0]);
    close(fd[1]);
    execlp("cat", "cat", NULL);
    exit(0);
    return 0;
}
