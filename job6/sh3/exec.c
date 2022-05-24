#include "root.h"
#include "lex.h"
#include "parse.h"
#include "exec.h"

//void tree_execute_basic(tree_t *this);
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

//	tree_dump(this);
	//puts("redirct");
	//if (((tree_t*)vector_get(&this->child_vector, 0))->type == TREE_BASIC)
	//	tree_execute_basic(this->child_vector.data[0]);
	//if (((tree_t*)vector_get(&this->child_vector, 0))->type == TREE_REDIRICT)
	//	tree_execute_redirect(this->child_vector.data[0]);
	//printf("%s\n", ((tree_t*)vector_get(&this->child_vector, 1))->token);
	//printf("%s\n", ((tree_t*)vector_get(&this->child_vector, 2))->token);
	
}

#define MAX_ARGC 16
void tree_execute_basic(tree_t *this)
{
//	tree_dump(this);
	//puts("basic");
	//for (int i = 0; i < this->child_vector.count; ++i){
	//	printf("%s\n", ((tree_t*)vector_get(&this->child_vector, i))->token);
	//}
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
//	tree_dump(this);
	//puts("pipe");
	//tree_execute_redirect((tree_t*)vector_get(&this->child_vector, 0));
	//if (this->child_vector.count == 2)
	//	tree_execute_pipe((tree_t*)vector_get(&this->child_vector, 1));
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
	//puts("back");
//	tree_dump(this);
	//for (int i = 0; i < this->child_count; ++i){
	//tree_execute_pipe((tree_t*)vector_get(&this->child_vector, 0));
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
