#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
    int fd = -1, i;
    ssize_t size = -1;
    char buf[11111];
    char *filename = argv[1];
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Open file %s failed.\n", filename);
        return 0;
    }
    while(size)
    {
        size = read(fd, buf, 11111);
        if (-1 == size)
        {
            close(fd);
            printf("Read file %s error occurs.\n", filename);
            return 0;
        }
        if (size > 0)
            for(i = 0; i < size; i++) 
                printf("%c",*(buf + i));
    }
    return 0;
}
