#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int tree(char* path, int tabnum){
    DIR* dirp = opendir(path);
    if(dirp != NULL) {
        for(;;) {
            struct dirent* direntp = readdir(dirp);
            if(direntp == NULL) break;
			if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0){
				printf("%*s\n", tabnum * 3, direntp->d_name);
				char nextpath[222];
				strcpy(nextpath, path);
				strcat(nextpath, "/");
				strcat(nextpath, direntp->d_name);
				DIR* nextdir = opendir(nextpath);
				if (nextdir != NULL){
					tree(nextpath, tabnum + 1);
					closedir(nextdir);
				}
			}
        }
        closedir(dirp);
        return EXIT_SUCCESS;
    }
}
int main(int argc, char *argv[])
{
    char *dirpath = argv[1];
	if (dirpath == NULL) dirpath = ".";
	else puts(dirpath);
	tree(dirpath, 1);
    return EXIT_FAILURE;
}
