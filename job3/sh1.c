#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
void mysys(char *command)
{
	if (strcmp(command, "exit") == 0) {
		exit(0);
	}
    pid_t pid;
    pid = fork();
    if (pid == 0){
		char *str = (char *)malloc(sizeof(command));
	    strcpy(str, command);
		char *p, *argv[11111];
        int i = 0, error = -1;
		p = strtok(str, " ");
        while(p != NULL) {
            argv[i++] = p;
            p = strtok(NULL, " ");
        }
        argv[i] = NULL;
		error = execvp(argv[0], argv);
        if (error == -1) {
            puts("exec error!");
            return;
        }
    }
    wait(NULL);
}

int main()
{
	char command[11111];
	int count;
    while (1){
		write(1, "> ", sizeof("> "));
		count = read(0, command, sizeof(command));
		command[count - 1] = 0;
        mysys(command);
    }
    return 0;
}
