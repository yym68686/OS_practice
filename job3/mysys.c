#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
void mysys(char *command)
{
    pid_t pid;
    pid = fork();
    if (pid == 0){
        char str[11111];
        strncpy(str, command, strlen(command) + 1);
        char *p, *argv[11111];
        int i = 0, error = -1;
        p = strtok(str, " ");
        while(p != NULL ) {
            argv[i++] = p;
            p = strtok(NULL, str);
        }
        argv[i] = NULL;
        error = execvp(argv[0], argv);
        if (error == -1) {
            printf("%s\n", argv[i - 1]);
            puts("exec error!");
            return;
        }
    }
    wait(NULL);
}

int main()
{
    printf("--------------------------------------------------\n");
    mysys("echo HELLO WORLD");
    printf("--------------------------------------------------\n");
    mysys("ls /");
    printf("--------------------------------------------------\n");
    return 0;
}
