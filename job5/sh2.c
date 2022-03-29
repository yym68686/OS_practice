#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
void mysys(char *command)
{
	//字符串处理
	char *str = (char *)malloc(sizeof(command)), *p, *argv[11111];
	int i = 0, error = -1;
	strcpy(str, command);
	p = strtok(str, " ");
	while(p != NULL) {
		argv[i++] = p;
		p = strtok(NULL, " ");
	}
	argv[i] = NULL;

	//内置指令
	if (strcmp(argv[0], "cd") == 0){
		int error = chdir(argv[1]);
		if (error >= 0){
			char *path = getcwd(NULL, 0);
			printf("%s\n", path);
			free(path);
		}
		else
			puts("change dir error!");
		return;
	}
	else if (strcmp(argv[0], "pwd") == 0) {
		char *path = getcwd(NULL, 0);
		printf("%s\n", path);
		free(path);
		return;
	}
	else if (strcmp(argv[0], "exit") == 0)
		exit(0);
	
	//多线程
	pid_t pid;
	int fd[2];
	pipe(fd);
	pid = fork();
	if (pid == 0){
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		error = execvp(argv[0], argv);
		if (error == -1) {
			puts("exec error!");
			exit(0);
		}
	}
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
}

int main()
{
	char command[11111];
	int count;
    while (1){
		//不能用scanf
		write(1, "> ", sizeof("> "));
		count = read(0, command, sizeof(command));
		command[count - 1] = 0;
        mysys(command);
    }
    return 0;
}
