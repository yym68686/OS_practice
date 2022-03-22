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
