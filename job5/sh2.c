#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
void mysys(char *command)
{
	//字符串处理
	char *str = (char *)malloc(sizeof(command)), *p, *argv[11111], *pipestr[] = {">", "<", ">>", "<<", "|"};
	int i = 0, error = -1, pipeflag = -1, pipestrflag = -1;
	strcpy(str, command);
	p = strtok(str, " ");
	while(p != NULL) {
		argv[i++] = p;
		for (int j = 0; j < sizeof(pipestr) / sizeof(pipestr[0]); j++)
			if (strcmp(pipestr[j], p) == 0)
				pipeflag = i - 1, pipestrflag = j;
		p = strtok(NULL, " ");
	}
	argv[i] = NULL;

	//内置指令
	if (pipeflag >= 0) {
		char *command1[111], *command2[111];
		int i = 0, j = 0, k = 0;
		while (i != pipeflag)
			command1[i++] = argv[k++];
		command1[i] = NULL, k++;
		while (j != sizeof(argv) / sizeof(argv[0]))
			command2[j++] = argv[k++];
		command2[j] = NULL;

		pid_t pid;
		int fd[2];
		pipe(fd);
		pid = fork();
		if (pid == 0){
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			if (pipestrflag == 0) {
				error = execvp(command1[0], command1);
				if (error == -1) {
					puts("exec error!");
					exit(0);
				}
			}
			else if (pipestrflag == 1){
				int fd = open(command2[0], O_RDONLY);
				char buf[111111];
				int count = read(fd, buf, sizeof(buf));
				buf[count - 1] = 0;
				write(1, buf, count - 1);
				close(fd);
			}
			exit(0);
		}
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		if (pipestrflag == 0) {
			char buf[1111];
			int count = read(0, buf, sizeof(buf));
			buf[count - 1] = 0;
			int fd = open(command2[0], O_WRONLY | O_CREAT | O_TRUNC);
			write(fd, buf, count - 1);
			close(fd);
		}
		else if (pipestrflag == 1){
			error = execvp(command1[0], command1);
			if (error == -1) {
				puts("exec error!");
				exit(0);
			}
		}
		return;
	}
	else if (strcmp(argv[0], "cd") == 0){
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
	pid = fork();
	if (pid == 0){
		error = execvp(argv[0], argv);
		if (error == -1) {
			puts("exec error!");
			exit(0);
		}
	}
	wait(NULL);
}

int main()
{
	char command[11111];
	int count, fdin = dup(0), fdout = dup(1);
    while (1){
		//不能用scanf
		dup2(fdin, 0);
		dup2(fdout, 1);
		write(1, "> ", sizeof("> "));
		count = read(0, command, sizeof(command));
		if (count == 1) continue;
		command[count - 1] = 0;
        mysys(command);
    }
    return 0;
}
