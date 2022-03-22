#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
	DIR* dirp;
    char *dirpath = argv[1];
	struct dirent* direntp;
	if (dirpath == NULL){
		dirpath = ".";
	}
    dirp = opendir(dirpath);
    if(dirp != NULL) {
        for(;;) {
            direntp = readdir(dirp);
            if(direntp == NULL) break;
			if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0)
				printf("%s\n", direntp->d_name);
        }
        closedir(dirp);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
// {
//     int fd = -1, i;
//     ssize_t size = -1;
//     char buf[11111];
//     char *filename = argv[1];
//     fd = open(filename, O_RDONLY);
//     if (fd == -1) {
//         printf("Open file %s failed.\n", filename);
//         return 0;
//     }
//     size = read(fd, buf, 11111);
//     if (-1 == size)
//     {
//         close(fd);
//         printf("Read file %s error occurs.\n", filename);
//         return 0;
//     }
//     if (size > 0)
//         for(i = 0; i < size; i++)
//             printf("%c",*(buf + i));
//     return 0;
// }
