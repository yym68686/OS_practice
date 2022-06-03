#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void find_file(char *path, char *target)
{
    FILE *file = fopen(path, "r");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, target))
            printf("%s: %s", path, line);
    }
    fclose(file);
}

void find_dir(char *path, char *target)
{
    DIR *dir = opendir(path);
    struct dirent *entry;
	char basepath[88];
    while (entry = readdir(dir)) {
        if (strcmp(entry->d_name, ".") == 0)
            continue;
        if (strcmp(entry->d_name, "..") == 0)
            continue;
        if (entry->d_type == DT_DIR){
			memset(basepath, 0, sizeof(basepath));
			strcpy(basepath, path);
			strcat(basepath, "/");
			strcat(basepath, entry->d_name);
			find_dir(basepath, target);
		}
        if (entry->d_type == DT_REG){
			memset(basepath, 0, sizeof(basepath));
			strcpy(basepath, path);
			strcat(basepath, "/");
			strcat(basepath, entry->d_name);
			find_file(basepath, target);
		}
    }
    closedir(dir);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        puts("Usage: sfind file string");
        return 0;
    }
    char *path = argv[1];
    char *string = argv[2];
    struct stat info;
    stat(path, &info);
    if (S_ISDIR(info.st_mode))
        find_dir(path, string);
    else
        find_file(path, string);
    return 0;
}
