#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
    int fd1 = -1, fd2 = -1, i;
    ssize_t size1 = -1;
    ssize_t size2 = -1;
    char buf[11111];
    char *sourcefile = argv[1];
    char *targetfile = argv[2];
    fd1 = open(sourcefile, O_RDONLY);
    fd2 = open(targetfile, O_WRONLY | O_CREAT);
    if (fd1 == -1) {
        printf("Open file %s failed.\n", sourcefile);
        return 0;
    }
    if (fd2 == -1) {
        printf("Open file %s failed.\n", targetfile);
        return 0;
    }
    size1 = read(fd1, buf, 11111);
    if (size1 == -1)
    {
        close(fd1);
        printf("Read file %s error occurs.\n", sourcefile);
        return 0;
    }
    if (size1 > 0){
        size2 = write(fd2, buf, size1);
        if (size2 == -1){
            close(fd1);
            printf("Copy file %s failed.\n", sourcefile);
            return 0;
        }
    }
    return 0;
}
