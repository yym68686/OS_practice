#include "root.h"
#include "lex.h"
#include "parse.h"
#include "exec.h"

// echo abc >log
//
// redirect
//   basic
//   >
//   log
//
// Inside child process
//
// cat <input >ouput
// redirct
//   redirect
//     basic
//       cat
//     <
//     input
//  >
//  output
void tree_execute_redirect(tree_t *this)
{
	puts("redirct");
	if (child_vector[0]->type == TREE_BASIC)
		tree_execute_basic(child_vector[0]);
	if (child_vector[0]->type == TREE_REDIRICT)
		tree_execute_redirect(child_vector[0]);
	printf("%s\n", child_vector[1]);
	printf("%s\n", child_vector[2]);
	
}

#define MAX_ARGC 16
void tree_execute_basic(tree_t *this)
{
	puts("basic");
	for (int i = 0; i < this->child_count; ++i){
		printf("%s\n", child_vector[i]->token);
	}
}

// echo abc | grep b
//
// pipe
//   basic
//     echo
//     abc
//   basic
//     grep
//     b
//
// cmdA | cmdB | cmdC
// pipe
//   pipe 
//     cmdA
//     cmdB
//   cmdC
void tree_execute_pipe(tree_t *this)
{
	puts("pipe");
	tree_execute_redirect(child_vector[0]);
	if (this->child_count == 2)
		tree_execute_pipe(child_vector[1]);
}

// # line 
// "cd /bin"
//
// # tree
// TREE_BASIC
//   cd
//   /bin
int tree_execute_builtin(tree_t *this)
{
    return 0;
}

// cc a-very-large-file.c &
// async
//   basic
//     cc
//     a-very-large-file
//
// cat file | grep string &
// async
//   pipe
//     basic
//       cat
//       file
//     basic
//       grep
//       string
//
// child count == 1
void tree_execute_async(tree_t *this)
{
	puts("back");
	//for (int i = 0; i < this->child_count; ++i){
	tree_execute_pipe(child_vector[0]);
	//}
}

// Inside child process
void tree_execute(tree_t *this)
{
    switch (this->type) {
        case TREE_ASYNC:
            tree_execute_async(this); 
            break;

        case TREE_PIPE:
            tree_execute_pipe(this); 
            break;

        case TREE_REDIRICT:
            tree_execute_redirect(this); 
            break;

        case TREE_BASIC:
              tree_execute_basic(this); 
            break;
    }
}

// Inside parent(shell) process
void tree_execute_wrapper(tree_t *this)
{
    if (tree_execute_builtin(this))
        return;

    int status;
    pid_t pid = fork();
    if (pid == 0) {
        tree_execute(this);
        exit(EXIT_FAILURE);
    }
   
    // cc a-large-file.c &
    if (this->type != TREE_ASYNC)
        wait(&status);
}

// cmd1 <input | cmd2 | cmd3 >output &
