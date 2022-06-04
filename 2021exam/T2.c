#include <stdio.h>
#include <string.h>
void find_file(char *path, char *target){
	FILE *file = fopen(path, "r");
	char line[256];
	while (fgets(line, sizeof(line), file))
		if (strstr(line, target))
			printf("%s", line);
	fclose(file);
}
int main(int argc, char *argv[]){
	char *string = argv[1];
	char *file = argv[2];
	find_file(file, string);
}
