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
            puts("exec error!");
            return;
        }
        puts("");
    }
    wait(NULL);
}

int main()
{
    char s[11111];
    do{
        printf("> ");
        scanf("%[^\n]", s);
        mysys(s);
    }while (s != "exit");
    return 0;
}
