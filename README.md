# 2022南航计算机学院操作系统实践

- [2022南航计算机学院操作系统实践](#2022南航计算机学院操作系统实践)
- [Job1](#job1)
  - [实验内容](#实验内容)
- [Job2](#job2)
  - [实验内容](#实验内容-1)
- [Job3](#job3)
  - [文件读写编程题目](#文件读写编程题目)
    - [job3/myecho.c](#job3myechoc)
    - [job3/mycat.c](#job3mycatc)
    - [job3/mycp.c](#job3mycpc)
  - [多进程题目](#多进程题目)
    - [job3/mysys.c: 实现函数mysys，用于执行一个系统命令，要求如下](#job3mysysc-实现函数mysys用于执行一个系统命令要求如下)
    - [job3/sh1.c](#job3sh1c)
- [Job4](#job4)
  - [job3/sh1.c](#job3sh1c-1)
  - [job4/test](#job4test)
  - [job4/myls.c](#job4mylsc)
  - [job4/mytree.c](#job4mytreec)
- [Job5](#job5)
  - [job5/sh2.c](#job5sh2c)
- [Job6](#job6)
  - [实验要求](#实验要求)
  - [实验过程](#实验过程)
    - [实现后台命令执行函数](#实现后台命令执行函数)
    - [实现基本命令执行函数](#实现基本命令执行函数)
    - [实现重定向命令执行函数](#实现重定向命令执行函数)
    - [实现管道命令执行函数](#实现管道命令执行函数)
    - [实现自定义命令](#实现自定义命令)
  - [源码分析](#源码分析)
- [Job7](#job7)
  - [实验内容](#实验内容-2)
  - [实验过程](#实验过程-1)
- [Job8](#job8)
  - [实验内容](#实验内容-3)
  - [实验过程](#实验过程-2)
- [Job9](#job9)
  - [实验内容](#实验内容-4)
  - [实验过程](#实验过程-3)
- [Job10](#job10)
  - [实验内容](#实验内容-5)
  - [实验过程](#实验过程-4)
- [References](#references)

项目地址：

[yym68686/OS_practice: NUAA 操作系统实践作业 (github.com)](https://github.com/yym68686/OS_practice)

课程网站：

[https://www.nuaalab.cn](https://www.nuaalab.cn/)

# Job1

## 实验内容

在 linux 环境中建立如下目录：

```
job1
├── dir
│ ├── a
│ ├── b
│ ├── c
│ ├── world.bak
│ └── world.c
├── dir.bak
│ ├── a
│ ├── b
│ ├── c
│ ├── world.bak
│ └── world.c
├── hello.bak
└── hello.c
```

文件内容如下： 

- 文件 a 是一个空文件 
- 文件 b 是一个空文件 
- 文件 c 是一个空文件 
- 文件 hello.c

```c
#include <stdio.h>
int main()
{
    puts("hello");
    return 0;
}
```

- 文件 hello.bak 与文件 hello.c 相同 
- 文件 world.c

```c
#include <stdio.h>
int main()
{
    puts("world");
    return 0;
}
```

- 文件 world.bak 与文件 world.c 相同
- 目录 dir.bak 内容与目录 dir 相同

# Job2

## 实验内容

- 在 gitee 上注册

- 把第一次作业复制到 gitee 的仓库中

```
job1
├── dir
│ ├── a
│ ├── b
│ ├── c
│ ├── world.bak
│ └── world.c
├── dir.bak
│ ├── a
│ ├── b
│ ├── c
│ ├── world.bak
│ └── world.c
├── hello.bak
└── hello.c
```

- 为程序 job2/make 编写 Makefile

```
job2
└── make
	├── main.c
	├── Makefile
	└── math.c
```

main.c 内容

```c
int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

```

math.c 内容

```c
#include <stdio.h>
extern int max(int a, int b);
extern int min(int a, int b)
int main()
{
    printf("min = %d\n", min(1, 2));
    printf("max = %d\n", max(1, 2));
    return 0;
}
```



- 你的代码仓库的目录结构如下，不要修改此结构

```
.
├── job1
│ ├── dir
│ │ ├── a
│ │ ├── b
│ │ ├── c
│ │ ├── world.bak
│ │ └── world.c
│ ├── dir.bak
│ │ ├── a
│ │ ├── b
│ │ ├── c
│ │ ├── world.bak
│ │ └── world.c
│ ├── hello.bak
│ └── hello.c
└── job2
	└── make
		├── main.c
		├── Makefile
		└── math.
```

# Job3

## 文件读写编程题目

### job3/myecho.c

- myecho.c的功能与系统echo程序相同

- 接受命令行参数，并将参数打印出来，例子如下：

  ```
  $ ./myecho x
  x
  $ ./myecho a b c
  a b c
  ```

### job3/mycat.c

- mycat.c的功能与系统cat程序相同

- mycat将指定的文件内容输出到屏幕，例子如下：

- 要求使用系统调用open/read/write/close实现

  ```
  $ cat /etc/passwd 
  root:x:0:0:root:/root:/bin/bash
  daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
  bin:x:2:2:bin:/bin:/usr/sbin/nologin
  ...
  $ ./mycat /etc/passwd 
  root:x:0:0:root:/root:/bin/bash
  daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
  bin:x:2:2:bin:/bin:/usr/sbin/nologin
  ...
  ```

### job3/mycp.c

- mycp.c的功能与系统cp程序相同

- 将源文件复制到目标文件，例子如下：

- 要求使用系统调用open/read/write/close实现

  ```
  $ cat /etc/passwd
  root:x:0:0:root:/root:/bin/bash
  daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
  bin:x:2:2:bin:/bin:/usr/sbin/nologin
  ...
  $ ./mycp /etc/passwd passwd.bak 
  $ cat passwd.bak
  root:x:0:0:root:/root:/bin/bash
  daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
  bin:x:2:2:bin:/bin:/usr/sbin/nologin
  ...
  ```

## 多进程题目

### job3/mysys.c: 实现函数mysys，用于执行一个系统命令，要求如下

- mysys的功能与系统函数system相同，要求用进程管理相关系统调用自己实现一遍

- **使用fork/exec/wait系统调用实现mysys**

- 不能通过调用系统函数system实现mysys

- 测试程序

  ```c
  #include <stdio.h>
  
  void mysys(char *command)
  {
      实现该函数，该函数执行一条命令，并等待该命令执行结束
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
  ```

- 测试程序的输出结果

  ```
  --------------------------------------------------
  HELLO WORLD
  --------------------------------------------------
  bin    core  home	     lib	 mnt   root  snap  tmp	vmlinuz
  boot   dev   initrd.img      lost+found  opt   run   srv   usr	vmlinuz.old
  cdrom  etc   initrd.img.old  media	 proc  sbin  sys   var
  --------------------------------------------------
  ```

### job3/sh1.c

- 该程序读取用户输入的命令，调用函数mysys(上一个作业)执行用户的命令，示例如下

  ```
  # 编译sh1.c
  $ cc -o sh1 sh1.c
  
  # 执行sh1
  $ ./sh 
  
  # sh1打印提示符>，同时读取用户输入的命令echo，并执行输出结果
  > echo a b c
  a b c
  
  # sh1打印提示符>，同时读取用户输入的命令cat，并执行输出结果
  > cat /etc/passwd
  root:x:0:0:root:/root:/bin/bash
  daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
  bin:x:2:2:bin:/bin:/usr/sbin/nologin
  ```

- 实现内置命令cd、pwd、exit



# Job4

## job3/sh1.c

- 完善job3的 sh1 功能
- 实现内置命令cd、pwd、exit

## job4/test

- 在代码仓库中创建 job4 目录

- 在代码仓库中创建 job4/test 目录

- job4/test 目录内容如下

  ```
  test
  ├── a
  ├── b
  │   ├── x
  │   ├── y
  │   └── z
  └── c
  
  test/a      普通文件
  test/b      目录
  test/c      普通文件
  test/b/x    普通文件
  test/b/y    普通文件
  test/b/z    普通文件
  ```

## job4/myls.c

- myls.c的功能与系统ls程序相同

- opendir readdir closedir

- 在命令行中输入 man opendir 获取帮助

- 列出指定目录下的文件，例子如下：

  ```
  $ ./myls job4/test
  a
  b
  c
  ```

- 列出当前目录下的文件，例子如下：

  ```
  $ cd job4/test 
  $ ./myls
  a
  b
  c
  ```

## job4/mytree.c

- mytree.c的功能与系统tree程序相同

- 使用空格作为缩进，表示层次

  ```
  $ ./mytree job4/test
  test
    a
    b
      x
      y
      z
    c
  ```

# Job5

## job5/sh2.c

实现shell程序，要求在第1版的基础上，增加文件重定向功能

- 重定向输入
- 重定向输出
- 重定向追加

# Job6

## 实验要求

实现shell程序，要求支持基本命令、重定向命令、管道命令、后台命令

- 使用结构体 tree 描述命令

- 参考代码下载

  ```
  enum {
      TREE_BACK,
      TREE_PIPE,
      TREE_REDIRICT,
      TREE_BASIC,
      TREE_TOKEN,
  };
  
  #define MAX_CHILD 10
  typedef struct {
      int type;
      char *token;
      int child_count;
      tree_t *child_vector[MAX_CHILD];
  } tree_t;
  
  "echo abc"
  + TREE_BASIC
    + child_vector
      + TREE_TOKEN
        + token = "echo"
      + TREE_TOKEN
        + token = "abc"
  
  "echo abc >log"
  + TREE_REDIRICT
    + TREE_BASIC
      + child_vector
        + TREE_TOKEN
          + token = "echo"
        + TREE_TOKEN
          + token = "abc"
    + TREE_TOKEN  
      + token = "<"
    + TREE_TOKEN  
      + token = "log"
  ```

- 从命令行中读取一行命令，输出该命令的结构

  ```
  echo abc | wc -l
  pipe
    basic
      echo
      abc
    basic
      wc
      -l
  
  cat main.c | grep int | wc -l
  pipe
    pipe
      basic
        cat
        main.c
      basic
        grep
        int
    basic
      wc
      -l
  
  echo abc | wc -l >log
  pipe
    basic
      echo
      abc
    redirect
      basic
        wc
        -l
      >
      log
  
  redirect
    pipe
      basic
        echo
        abc
      basic
        wc
        -l
    >
    log
  
  gcc big.c &
  back
    basic
      gcc
      big.c
  
  echo abc | wc -l &
  back
    pipe
      basic
        echo
        abc
      basic
        wc
        -l
  
  cat <input >output
  redirect
    redirect
      basic 
        cat
      <
      input
    >
    output
  ```

## 实验过程

### 实现后台命令执行函数

```c
void tree_execute_async(tree_t *this)
{
    tree_t *body = tree_get_child(this, 0);
    tree_execute(body);
}
```

后台执行命令只有`child_count`只有两个。`cmd &`因为最后一个字符一定是`&`，所以直接执行`cmd`就好了。

### 实现基本命令执行函数

```c
void tree_execute_basic(tree_t *this)
{
    int argc = 0;
    char *argv[MAX_ARGC];

    int i;
    tree_t *child;
    vector_each(&this->child_vector, i, child)
        argv[argv++] = child->token;
    argv[argc] = NULL;
    execvp(argv[0], argv);

    perror("exec");
    exit(EXIT_FAILURE);
} 
```

### 实现重定向命令执行函数

```c
void tree_execute_redirect(tree_t *this)
{
    tree_t *body = tree_get_child(this, 0);
    tree_t *operator = tree_get_child(this, 1);
    tree_t *file = tree_get_child(this, 2);
    char *path;
    int fd;
    int redirect_fd;

    path = file->token;
    if (token_is(operator, "<")) {
        fd = open(path, O_RDONLY);
        assert(fd >= 0);
        dup2(fd, 0);
        close(fd);
    }
    if (token_is(operator, ">")) {
        fd = creat(path, 0666);
        assert(fd >= 0);
        dup2(fd, 1);
        close(fd);
    }
    tree_execute(body);
}
```

### 实现管道命令执行函数

```c
void tree_execute_pipe(tree_t *this)
{
    int fd[2];
    pid_t pid;
    tree_t *left = tree_get_child(this, 0);
    tree_t *right = tree_get_child(this, 1);
    pipe(fd);
    pid = fork();
    if (pid == 0) {
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        tree_execute(left);
        exit(EXIT_FAILURE);
    }
    close(0);
    dup(fd[0]);
    close(fd[0]);
    close(fd[1]);
    tree_execute(right);
}
```

### 实现自定义命令

```c
int tree_execute_builtin(tree_t *this)
{
    if (this->type != TREE_BASIC)
        return 0;
    int argc = this->child_vector.count;
    tree_t *child0 = tree_get_child(this, 0);
    char *arg0 = child0->token;

    if (strcmp(arg0, "exit") == 0) {
        exit(EXIT_FAILURE);
        return 1;
    }

    if (strcmp(arg0, "pwd") == 0) {
        char buf[128];
        getcwd(buf, sizeof(buf));
        puts(buf);
        return 1;
    }

    if (strcmp(arg0, "cd") == 0) {
        if (argc == 1)
            return 1;
        tree_t *child1 = tree_get_child(this, 1);
        char *arg1 = child1->token;
        int error = chdir(arg1);
        if (error < 0)
            perror("cd");
        return 1;
    }
    return 0;
}
```

编译运行：

```bash
cd ~/OS_practice/job6/sh3 && make clean && make && ./sh
```

测试命令：

```bash
cat exec.c | wc -l >1
```

成功显示290。

## 源码分析

parse.h 中的 tree 的数据结构，源代码：

```c
enum {
    TREE_ASYNC,     // cmd &
    TREE_PIPE,      // cmdA | cmdB
    TREE_REDIRICT,  // cmd >output <input
    TREE_BASIC,     // cmd arg1 arg2
    TREE_TOKEN,     // leaf
};

typedef struct {
    int type;
    char *token;            // TREE_TOKEN
    vector_t child_vector;  // other tree
} tree_t;
```

- 其中type是记录这棵树是什么类型的命令，type所有可能通过枚举类型列出：后台命令，管道命令，基本命令，重定向命令，把命令分割成词的token类型。

- token字段表示命令以词分割的一段字符串。

- child_vector字段表示当前树下子树的数组。

main.c 源代码

```c
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "parse.h"
#include "exec.h"

int verbose = 0;

void execute_line(char *line)
{
    tree_t *tree;
    lex_init(line);
    tree = parse_tree();
    if (verbose)
        tree_dump(tree, 0);
    if (tree != NULL)
        tree_execute_wrapper(tree), tree_dump(tree, 0);
    lex_destroy();
}

void read_line(char *line, int size)
{
    int count;

    count = read(0, line, size);
    if (count == 0)
        exit(EXIT_SUCCESS);
    assert(count > 0);
    if ((count > 0) && (line[count - 1] == '\n'))
        line[count - 1] = 0;
    else
        line[count] = 0;
}

void read_and_execute()
{
    char line[128];

    write(1, "# ", 2);
    read_line(line, sizeof(line));
    execute_line(line);
}

void test()
{
    execute_line("cat /etc/passwd | sort | grep root >log");
}

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-v") == 0)
        verbose = 1;
    while (1)
        read_and_execute();
    return 0;
}
```

- 先看main函数，先判断是否含有`-v`参数，如果有这个参数就会打印语法分析树，然后不断循环跳转到read_and_execute函数以行读取指令。

- 在read_and_execute中以行读取指令，并且跳转到execute_line函数执行指令。

- 在execute_line函数中，先进行词法分析，建立语法分析树，跳转到tree_execute_wrapper函数执行指令。tree_execute_wrapper函数在exec.c中。

exec.c 的源代码：

```c
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
    tree_t *body = tree_get_child(this, 0);
    tree_t *operator = tree_get_child(this, 1);
    tree_t *file = tree_get_child(this, 2);
    char *path;
    int fd;

    path = file->token;
    if (token_is(operator, "<")) {
        fd = open(path, O_RDONLY);
        assert(fd >= 0);
        dup2(fd, 0);
        close(fd);
    }
    if (token_is(operator, ">")) {
        fd = creat(path, 0666);
        assert(fd >= 0);
        dup2(fd, 1);
        close(fd);
    }
    tree_execute(body);
}

#define MAX_ARGC 16
void tree_execute_basic(tree_t *this)
{
    int argc = 0;
    char *argv[MAX_ARGC];

    int i;
    tree_t *child;
    vector_each(&this->child_vector, i, child)
        argv[argc++] = child->token;
    argv[argc] = NULL;
    execvp(argv[0], argv);

    perror("exec");
    exit(EXIT_FAILURE);
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
    int fd[2];
    pid_t pid;
    tree_t *left = tree_get_child(this, 0);
    tree_t *right = tree_get_child(this, 1);

    pipe(fd);
    pid = fork();
    if (pid == 0) {
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        tree_execute(left);
        exit(EXIT_FAILURE);
    }
    close(0);
    dup(fd[0]);
    close(fd[0]);
    close(fd[1]);
    tree_execute(right);
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
    if (this->type != TREE_BASIC)
        return 0;
    int argc = this->child_vector.count;
    tree_t *child0 = tree_get_child(this, 0);
    char *arg0 = child0->token;

    if (strcmp(arg0, "exit") == 0) {
        exit(EXIT_FAILURE);
        return 1;
    }

    if (strcmp(arg0, "pwd") == 0) {
        char buf[128];
        getcwd(buf, sizeof(buf));
        puts(buf);
        return 1;
    }

    if (strcmp(arg0, "cd") == 0) {
        if (argc == 1)
            return 1;
        tree_t *child1 = tree_get_child(this, 1);
        char *arg1 = child1->token;
        int error = chdir(arg1);
        if (error < 0)
            perror("cd");
        return 1;
    }
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
    tree_t *body = tree_get_child(this, 0);
    tree_execute(body);
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
```

- 程序运行到tree_execute_wrapper函数，先创建一个子线程，然后跳转到tree_execute函数执行命令。
- 在tree_execute函数中，通过type判断属于什么命令类型。根据命令类型去到相应的执行函数里面，一共有四个具体的执行函数，分别是：tree_execute_async，tree_execute_pipe，tree_execute_basic，tree_execute_redirect。
- 其中tree_execute_async函数，直接执行命令。
- tree_execute_pipe函数，用进程创建子进程，用重定向命令把标准输入输出重定向到管道，分别执行管道左边和右边的命令。
- tree_execute_basic函数，获取命令所有的参数组成参数数组，用execvp函数执行参数数组。
- tree_execute_redirect函数，先判断是重定向输入还是重定向输出，把标准输入输出重定向到文件，最后执行命令。

# Job7

## 实验内容

多线程题目

1. job7/pi1.c: 使用2个线程根据莱布尼兹级数计算PI

- 莱布尼兹级数公式: 1 - 1/3 + 1/5 - 1/7 + 1/9 - ... = PI/4
- 主线程创建1个辅助线程
- 主线程计算级数的前半部分
- 辅助线程计算级数的后半部分
- 主线程等待辅助线程运行結束后,将前半部分和后半部分相加

2. job7/pi2.c: 使用N个线程根据莱布尼兹级数计算PI

- 与上一题类似，但本题更加通用化，能适应N个核心
- 主线程创建N个辅助线程
- 每个辅助线程计算一部分任务，并将结果返回
- 主线程等待N个辅助线程运行结束，将所有辅助线程的结果累加
- 本题要求 1: 使用线程参数，消除程序中的代码重复
- 本题要求 2: 不能使用全局变量存储线程返回值

3. job7/sort.c: 多线程排序

- 主线程创建两个辅助线程
- 辅助线程1使用选择排序算法对数组的前半部分排序
- 辅助线程2使用选择排序算法对数组的后半部分排序
- 主线程等待辅助线程运行結束后,使用归并排序算法归并子线程的计算结果
- 本题要求 1: 使用线程参数，消除程序中的代码重复

## 实验过程

pi1.c

```c
#include <stdio.h>
#include <pthread.h>
#define NUMBER 1000000

double worker_output;
void *worker(void *arg)
{
    for (int i = 1; i <= NUMBER / 2; i++)
        worker_output += (i % 2 == 0 ? -1 : 1) * 1.0 / (2 * i - 1);
    return NULL;
}

double master_output;
void master()
{
    for (int i = NUMBER / 2 + 1; i <= NUMBER; i++)
        master_output += (i % 2 == 0 ? -1 : 1) * 1.0 / (2 * i - 1);
}

int main()
{
    pthread_t worker_tid;
    double total;

    pthread_create(&worker_tid, NULL, worker, NULL);
    master();
    pthread_join(worker_tid, NULL);
    total = (master_output + worker_output) * 4;
    printf("PI = %f\n", total);
    return 0;
}
```

pi2.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NR_TOTAL 1000000
#define NR_CPU 2
#define NR_CHILD (NR_TOTAL/NR_CPU)

struct param {
    int start;
    int end;
};

struct result {
    double sum;
};

void *compute(void *arg)
{
        struct param *param;
        struct result *result;
    double sum = 0;
    param = (struct param *)arg;

    for (int i = param->start; i <= param->end; i++)
        sum += (i % 2 == 0 ? -1 : 1) * 1.0 / (2 * i - 1);

    result = malloc(sizeof(struct result));
    result->sum = sum;
    return result;
}

int main()
{
    pthread_t workers[NR_CPU];
    struct param params[NR_CPU];

    for (int i = 0; i < NR_CPU; i++) {
        struct param *param;
        param = &params[i];
        param->start = i * NR_CHILD + 1;
        param->end = (i + 1) * NR_CHILD;
        pthread_create(&workers[i], NULL, compute, param);
    }

    double sum = 0;
    for (int i = 0; i < NR_CPU; i++) {
        struct result *result;
        pthread_join(workers[i], (void **)&result);
        sum += result->sum;
        free(result);
    }
    printf("PI = %f\n", sum * 4);
    return 0;
}
```

- 创建线程，用结构体构建线程参数，包括计算开始字符和结束字符。
- 用for循环创建线程，同时把线程参数传到线程里。
- 在 compute 线程里，根据传进来的参数确定计算的起始位置和终止位置，通过for循环相加，最后通过开辟内存空间回传计算结果。
- 在主线程等待线程全部执行完毕，把结果加起来。

sort.c

```c
#include <stdio.h>
#include <pthread.h>

int array[] = {6, 5, 4, 3, 2, 1, 0, 100, -1};
#define NUMBER sizeof(array) / sizeof(int)

void *worker(void *arg)
{
    for (int i = 0; i < NUMBER / 2; i++){
        int minIndex = i;
        for (int j = i + 1; j <  NUMBER / 2; j++)
            if (array[minIndex] > array[j])
                minIndex = j;
        int temp = array[minIndex];
        array[minIndex] = array[i];
        array[i] = temp;
    }
    return NULL;
}

void master()
{
    for (int i = NUMBER / 2; i < NUMBER; i++){
        int minIndex = i;
        for (int j = i + 1; j <  NUMBER; j++)
            if (array[minIndex] > array[j])
                minIndex = j;
        int temp = array[minIndex];
        array[minIndex] = array[i];
        array[i] = temp;
    }
}

void Merge(){
    int i = 0;//左序列指针
    int j = NUMBER / 2;//右序列指针
    int t = 0;//临时数组指针
    int left = 0;
    int right = NUMBER - 1;
    int mid = NUMBER / 2 - 1;
    int temp[NUMBER];
    while (i <= mid && j <= right){
        if(array[i] <= array[j])
            temp[t++] = array[i++];
        else
            temp[t++] = array[j++];
    }
    while(i <= mid)//将左边剩余元素填充进temp中
        temp[t++] = array[i++];
    while(j <= right)//将右序列剩余元素填充进temp中
        temp[t++] = array[j++];
    //将temp中的元素全部拷贝到原数组中
    t = 0;
    while(left <= right)
        array[left++] = temp[t++];
}

int main()
{
    pthread_t worker_tid;
    pthread_create(&worker_tid, NULL, worker, NULL);
    master();
    pthread_join(worker_tid, NULL);
    Merge();
    for (int i = 0; i < NUMBER; i++)
        printf("%d ", array[i]);
    puts("");
    return 0;
}
```

# Job8

## 实验内容

1. job8/pc.c: 使用条件变量解决生产者、计算者、消费者问题

+ 系统中有3个线程：生产者、计算者、消费者

+ 系统中有2个容量为4的缓冲区：buffer1、buffer2

+ 生产者
  - 生产'a'、'b'、'c'、‘d'、'e'、'f'、'g'、'h'八个字符
  - 放入到buffer1
  - 打印生产的字符
  
+ 计算者
  - 从buffer1取出字符
  - 将小写字符转换为大写字符，按照 input:OUTPUT 的格式打印
  - 放入到buffer2
  
+ 消费者
  - 从buffer2取出字符
  - 打印取出的字符
  
+ 程序输出结果(实际输出结果是交织的)

  a
  b
  c
  ...
    a:A
    b:B
    c:C
    ...
        A
        B
        C
        ...

2. job8/pp.c: 使用条件变量实现 ping-pong 问题

+ 系统中有2个线程：ping 线程和 pong 线程
+ ping 线程先执行
+ ping 线程执行流程如下
  1. 打印输出 ping
  2. 等待 pong 线程输出
  3. 执行第 1 步
+ pong 线程执行流程如下
  1. 打印输出 pong
  2. 等待 ping 线程输出
  3. 执行第 1 步
+ 程序输出结果
  ping
  pong
  ping
  pong
  ...

## 实验过程

pc.c

```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY1 4
#define CAPACITY2 4
int buffer1[CAPACITY1];
int buffer2[CAPACITY2];
int in1, in2;
int out1, out2;

int buffer1_is_empty(){
    return in1 == out1;
}
int buffer2_is_empty(){
    return in2 == out2;
}

int buffer1_is_full(){
    return (in1 + 1) % CAPACITY1 == out1;
}
int buffer2_is_full(){
    return (in2 + 1) % CAPACITY2 == out2;
}

int get_item1(){
    int item;
    item = buffer1[out1];
    out1 = (out1 + 1) % CAPACITY1;
    return item;
}

int get_item2(){
    int item;
    item = buffer2[out2];
    out2 = (out2 + 1) % CAPACITY2;
    return item;
}

void put_item1(int item){
    buffer1[in1] = item;
    in1 = (in1 + 1) % CAPACITY1;
}

void put_item2(int item){
    buffer2[in2] = item;
    in2 = (in2 + 1) % CAPACITY2;
}

pthread_mutex_t mutex1;
pthread_cond_t wait_empty_buffer1;
pthread_cond_t wait_full_buffer1;
pthread_mutex_t mutex2;
pthread_cond_t wait_empty_buffer2;
pthread_cond_t wait_full_buffer2;

#define ITEM_COUNT (CAPACITY1 * 2)

void *consume(void *arg)
{
    int item;

    for (int i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex2);
        while (buffer2_is_empty())
            pthread_cond_wait(&wait_full_buffer2, &mutex2);

        item = get_item2();
        printf("    consume item: %c\n", item);

        pthread_cond_signal(&wait_empty_buffer2);
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}
void *computer(void *arg){
    int item;
    for (int i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex1);
        while (buffer1_is_empty())
            pthread_cond_wait(&wait_full_buffer1, &mutex1);
        item = get_item1();
        item -= 32;
        printf("computer get item: %c\n", item);
        pthread_cond_signal(&wait_empty_buffer1);
        pthread_mutex_unlock(&mutex1);

        pthread_mutex_lock(&mutex2);
        while (buffer2_is_full())
            pthread_cond_wait(&wait_empty_buffer2, &mutex2);
        put_item2(item);
        printf("    computer put item: %c\n", item);
        pthread_cond_signal(&wait_full_buffer2);
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

void *produce(void *arg)
{
    int item;

    for (int i = 0; i < ITEM_COUNT; i++) {
        pthread_mutex_lock(&mutex1);
        while (buffer1_is_full())
            pthread_cond_wait(&wait_empty_buffer1, &mutex1);

        item = 'a' + i;
        put_item1(item);
        printf("produce item: %c\n", item);

        pthread_cond_signal(&wait_full_buffer1);
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}

int main()
{
    pthread_t consumer_tid;
    pthread_t computer_tid;

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_cond_init(&wait_empty_buffer1, NULL);
    pthread_cond_init(&wait_empty_buffer2, NULL);
    pthread_cond_init(&wait_full_buffer1, NULL);
    pthread_cond_init(&wait_full_buffer2, NULL);

    pthread_create(&consumer_tid, NULL, consume, NULL);
    pthread_create(&computer_tid, NULL, computer, NULL);
    produce(NULL);
    pthread_join(consumer_tid, NULL);
    pthread_join(computer_tid, NULL);
    return 0;
}
```

- 先看主函数，先创建两个线程，初始化锁和条件变量，在主线程运行生产者函数，并等待计算着消费者子线程结束。
- 在生产者线程里，互斥生产字符到字符数组，并发送信号唤醒等待缓冲区满了的线程。
- 计算者线程被唤醒，将字符变成大写存到另外一个缓冲区里，再唤醒等待第二个缓冲区满了的线程。
- 消费者线程被唤醒，在第二个缓冲区拿出字符，同时唤醒等待缓冲区空的线程。

pp.c

```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t wait_print;
enum {
    PING,
    PONG
};
int state = PING;
void *ping(void *arg)
{
    int i = 10;
    while(i--){
        pthread_mutex_lock(&mutex);
        while (state != PING)
            pthread_cond_wait(&wait_print, &mutex);
        puts("ping");
        state = PONG;
        pthread_cond_signal(&wait_print);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *pong(void *arg)
{
    int i = 10;
    while(i--){
        pthread_mutex_lock(&mutex);
        while (state != PONG)
            pthread_cond_wait(&wait_print, &mutex);
        puts("pong");
        state = PING;
        pthread_cond_signal(&wait_print);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t ping_tid, pong_tid;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&wait_print, NULL);

    pthread_create(&ping_tid, NULL, ping, NULL);
    pthread_create(&pong_tid, NULL, pong, NULL);
    pthread_join(ping_tid, NULL);
    pthread_join(pong_tid, NULL);
    return 0;
}
```

pthread_cond_wait()被唤醒时，它解除阻塞，并且尝试获取锁（不一定拿到锁）。因此，一般在使用的时候都是在一个循环里使用pthread_cond_wait()函数，因为它在返回的时候不一定能拿到锁（这可能会发生饿死情形，当然这取决于操作系统的调度策略）。

# Job9

## 实验内容

关于信号量

1. 在[pthread 讲义](https://www.nuaalab.cn/courses/pthread/)中，条件变量章节的例子 2 说明了如何基于条件变量实现信号量
2. 请对比参考操作系统原理书中关于信号量的实现
3. 本节课要求基于信号量实现线程同步

- job9/pc.c: 使用信号量解决生产者、计算者、消费者问题

```
功能与 job8/pc.c 相同
```

- job9/pp.c: 使用信号量实现 ping-pong 问题

```
功能与 job8/pp.c 相同
```

## 实验过程

pc.c

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define CAPACITY1 4
#define CAPACITY2 4
int buffer1[CAPACITY1];
int buffer2[CAPACITY2];
int in1, in2;
int out1, out2;

int buffer1_is_empty(){
    return in1 == out1;
}
int buffer2_is_empty(){
    return in2 == out2;
}

int buffer1_is_full(){
    return (in1 + 1) % CAPACITY1 == out1;
}
int buffer2_is_full(){
    return (in2 + 1) % CAPACITY2 == out2;
}

int get_item1(){
    int item;
    item = buffer1[out1];
    out1 = (out1 + 1) % CAPACITY1;
    return item;
}

int get_item2(){
    int item;
    item = buffer2[out2];
    out2 = (out2 + 1) % CAPACITY2;
    return item;
}

void put_item1(int item){
    buffer1[in1] = item;
    in1 = (in1 + 1) % CAPACITY1;
}

void put_item2(int item){
    buffer2[in2] = item;
    in2 = (in2 + 1) % CAPACITY2;
}

typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} sema_t;

void sema_init(sema_t *sema, int value)
{
    sema->value = value;
    pthread_mutex_init(&sema->mutex, NULL);
    pthread_cond_init(&sema->cond, NULL);
}

void sema_wait(sema_t *sema)
{
    pthread_mutex_lock(&sema->mutex);
    while (sema->value <= 0)
        pthread_cond_wait(&sema->cond, &sema->mutex);
    sema->value--;
    pthread_mutex_unlock(&sema->mutex);
}

void sema_signal(sema_t *sema)
{
    pthread_mutex_lock(&sema->mutex);
    ++sema->value;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

sema_t mutex_sema1;
sema_t mutex_sema2;
sema_t empty_buffer_sema1;
sema_t empty_buffer_sema2;
sema_t full_buffer_sema1;
sema_t full_buffer_sema2;

#define ITEM_COUNT (CAPACITY1 * 2)

void *consume(void *arg)
{
    int item;
    for (int i = 0; i < ITEM_COUNT; i++) {
        sema_wait(&full_buffer_sema2);
        sema_wait(&mutex_sema2);

        item = get_item2();
        printf("    consume item: %c\n", item);

        sema_signal(&mutex_sema2);
        sema_signal(&empty_buffer_sema2);
    }

    return NULL;
}

void *computer(void *arg){
    int item;
    for (int i = 0; i < ITEM_COUNT; i++) {
        sema_wait(&full_buffer_sema1);
        sema_wait(&mutex_sema1);
        item = get_item1();
        item -= 32;
        printf("computer get item: %c\n", item);
        sema_signal(&mutex_sema1);
        sema_signal(&empty_buffer_sema1);

        sema_wait(&empty_buffer_sema2);
        sema_wait(&mutex_sema2);
        put_item2(item);
        printf("    computer put item: %c\n", item);
        sema_signal(&mutex_sema2);
        sema_signal(&full_buffer_sema2);
    }
    return NULL;
}

void *produce()
{
    int item;
    for (int i = 0; i < ITEM_COUNT; i++) {
        sema_wait(&empty_buffer_sema1);
        sema_wait(&mutex_sema1);

        item = i + 'a';
        put_item1(item);
        printf("produce item: %c\n", item);

        sema_signal(&mutex_sema1);
        sema_signal(&full_buffer_sema1);
    }
    return NULL;
}

int main()
{
    pthread_t consumer_tid, computer_tid;

    sema_init(&mutex_sema1, 1);
    sema_init(&mutex_sema2, 1);
    sema_init(&empty_buffer_sema1, CAPACITY1 - 1);
    sema_init(&empty_buffer_sema2, CAPACITY2 - 1);
    sema_init(&full_buffer_sema1, 0);
    sema_init(&full_buffer_sema2, 0);

    pthread_create(&consumer_tid, NULL, consume, NULL);
    pthread_create(&computer_tid, NULL, computer, NULL);
    produce();
    pthread_join(consumer_tid, NULL);
    pthread_join(computer_tid, NULL);
    return 0;
}
```

- 先看主函数，先创建两个线程，初始化信号量锁和信号量，将每个缓冲区的总容量赋值给信号量，在主线程运行生产者函数，并等待计算着消费者子线程结束。
- 在生产者线程里，互斥生产字符到字符数组，并将第一个缓冲区空区域减少一个，并获得第一个缓冲区的锁。结束后增加缓冲区的被占用的数量。
- 计算者线程被唤醒，将字符变成大写存到另外一个缓冲区里，第一个缓冲区空闲区域加一，占用区域减一，第二个缓冲区空闲区域减一，占用区域加一。第二个缓冲区有字符，消费者线程被唤醒。
- 消费者线程被唤醒，在第二个缓冲区拿出字符，第二个缓冲区空闲区域加一，占用区域减一，同时唤醒第二个缓冲区未满的计算着进程。

pp.c

```c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t wait_print;
enum {
    PING,
    PONG
};
int state = PING;

typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} sema_t;

void sema_init(sema_t *sema, int value)
{
    sema->value = value;
    pthread_mutex_init(&sema->mutex, NULL);
    pthread_cond_init(&sema->cond, NULL);
}

void sema_wait(sema_t *sema)
{
    pthread_mutex_lock(&sema->mutex);
    while (sema->value <= 0)
        pthread_cond_wait(&sema->cond, &sema->mutex);
    sema->value--;
    pthread_mutex_unlock(&sema->mutex);
}

void sema_signal(sema_t *sema)
{
    pthread_mutex_lock(&sema->mutex);
    ++sema->value;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

sema_t mutex_sema;
sema_t wait_print_ping;
sema_t wait_print_pong;

void *ping(void *arg)
{
    int i = 10;
    while(i--){
        sema_wait(&wait_print_ping);
        sema_wait(&mutex_sema);
        puts("ping");
        state = PONG;
        sema_signal(&mutex_sema);
        sema_signal(&wait_print_pong);
    }
    return NULL;
}

void *pong(void *arg)
{
    int i = 10;
    while(i--){
        sema_wait(&wait_print_pong);
        sema_wait(&mutex_sema);
        puts("pong");
        state = PING;
        sema_signal(&mutex_sema);
        sema_signal(&wait_print_ping);
    }
    return NULL;
}

int main()
{
    pthread_t ping_tid, pong_tid;

    sema_init(&mutex_sema, 1);
    sema_init(&wait_print_ping, 1);
    sema_init(&wait_print_pong, 1);

    pthread_create(&ping_tid, NULL, ping, NULL);
    pthread_create(&pong_tid, NULL, pong, NULL);
    pthread_join(ping_tid, NULL);
    pthread_join(pong_tid, NULL);
    return 0;
}
```



# Job10

## 实验内容

1. 串行查找 job10/sfind.c:

```
+ 系统中有3个线程：生产者、计算者、消费者
```

程序 sfind 在文件或者目录中查找指定的字符串，并打印包含该字符串的行，示例如下： 

- 在文件 file.c 中查找字符串 main
  - 找到包含字符串 main 的行
  - 打印文件名和该行

```bash
$ sfind file.c main
file.c: int main(int argc, char *argv[])
```

- 在目录 test 中查找字符串 main
  - 假设目录 test 下存在文件 
    - test/hello/hello.c 
    - test/world/world.c 
  - 对目录 test 下的所有文件进行查找 
  - 找到包含字符串 main 的行 
  - 打印文件名和该行

```bash
$ sfind test main
test/hello/hello.c: int main()
test/world/world.c: int main()
```

2. 并行查找 job10/pfind.c:

```
+ 系统中有3个线程：生产者、计算者、消费者
```

2.1 功能 

- 功能与 sfind 相同
- 要求使用多线程完成 
  - 主线程创建若干个子线程 
    - 主线程负责遍历目录中的文件
    - 遍历到目录中的叶子节点时 
    - 将叶子节点发送给子线程进行处理 
  - 两者之间使用生产者消费者模型通信 
    - 主线程生成数据 
    - 子线程读取数据

2.2 图示

- 主线程创建 2 个子线程 
  - 主线程遍历目录 test 下的所有文件 
  - 把遍历的叶子节点 path 和目标字符串 string，作为任务，发送到任务队列 
- 子线程 
  - 不断的从任务队列中读取任务 path 和 string 
  - 在 path 中查找字符串 string

![image-20220604203648519](images/image-20220604203648519.png)

2.3 参考程序

```c
#define WORKER_NUMBER 4
struct task {
    int is_end;
    char path[128];
    char string[128];
};
+ 子线程的入口
    - 在一个循环中
    - 从任务队列中，获取一个任务，去执行
    - 当读取到一个特殊的任务(is_end 为真)，循环结束
void *worker_entry(void *arg)
{
    while (1) {
        struct task task;
        从任务队列中获取一个任务 task;
        if (task->is_end)
            break;
        执行该任务;
        find_file(task->path, task->string);
    }
}
int main(int argc, char **argv[])
{
    char *path = argv[1];
    char *string = argv[2];
    if (path 是一个普通文件) {
        find_file(path, string);
        return;
    }
    1. 创建一个任务队列;
    - 初始化时，任务队列为空
    2. 创建 WORKER_NUMBER 个子线程;
    3. 对目录 path 进行递归遍历:
    - 遇见叶子节点时
        - 把叶子节点的路径加入到任务队列中
        4. 创建 WORER_NUMBER 个特殊任务
        - 特殊任务的 is_end 为真
        * 子线程读取到特殊任务时
        * 表示主线程已经完成递归遍历，不会再向任务队列中放置任务
        * 此时，子线程可以退出
        - 把这些特殊任务加入到任务队列中
        5. 等待所有的子线程结束;

```

## 实验过程

sfind.c

```c
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
```

stat结构体

```c
struct stat  
{   
    dev_t       st_dev;     /* ID of device containing file -文件所在设备的ID*/  
    ino_t       st_ino;     /* inode number -inode节点号*/    
    mode_t      st_mode;    /* protection -保护模式?文件、文件夹的标志*/    
    nlink_t     st_nlink;   /* number of hard links -链向此文件的连接数(硬连接)*/    
    uid_t       st_uid;     /* user ID of owner -user id*/    
    gid_t       st_gid;     /* group ID of owner - group id*/    
    dev_t       st_rdev;    /* device ID (if special file) -设备号，针对设备文件*/    
    off_t       st_size;    /* total size, in bytes -文件大小，字节为单位*/    
    blksize_t   st_blksize; /* blocksize for filesystem I/O -系统块的大小*/    
    blkcnt_t    st_blocks;  /* number of blocks allocated -文件所占块数*/    
    time_t      st_atime;   /* time of last access -最近存取时间*/    
    time_t      st_mtime;   /* time of last modification -最近修改时间*/    
    time_t      st_ctime;   /* time of last status change - */    
}; 
```

readdir()返回参数dir目录流的下个目录进入点。结构dirent定义如下：

```c
struct dirent
{
    ino_t d_ino; //d_ino 此目录进入点的inode
    ff_t d_off; //d_off 目录文件开头至此目录进入点的位移
    signed short int d_reclen; //d_reclen _name 的长度, 不包含NULL 字符
    unsigned char d_type; //d_type d_name 所指的文件类型 d_name 文件名
    har d_name[256];
};
```

返回值：成功则返回下个目录进入点. 有错误发生或读取到目录文件尾则返回NULL.

pfind.c

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

#define CAPACITY 40
int in;
int out;

struct task {
    int is_end;
    char path[128];
    char string[128];
};
struct task buffer[CAPACITY];

typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} sema_t;

void sema_init(sema_t *sema, int value)
{
    sema->value = value;
    pthread_mutex_init(&sema->mutex, NULL);
    pthread_cond_init(&sema->cond, NULL);
}

void sema_wait(sema_t *sema)
{
    pthread_mutex_lock(&sema->mutex);
    while (sema->value <= 0)
        pthread_cond_wait(&sema->cond, &sema->mutex);
    sema->value--;
    pthread_mutex_unlock(&sema->mutex);
}

void sema_signal(sema_t *sema)
{
    pthread_mutex_lock(&sema->mutex);
    ++sema->value;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

sema_t mutex_sema;
sema_t empty_buffer_sema;
sema_t full_buffer_sema;

struct task get_item()
{

    sema_wait(&full_buffer_sema);
    sema_wait(&mutex_sema);

    struct task item = buffer[out];
    out = (out + 1) % CAPACITY;

    sema_signal(&mutex_sema);
    sema_signal(&empty_buffer_sema);
    return item;
}

void put_item(struct task item)
{
    sema_wait(&empty_buffer_sema);
    sema_wait(&mutex_sema);

    buffer[in] = item;
    in = (in + 1) % CAPACITY;

    sema_signal(&mutex_sema);
    sema_signal(&full_buffer_sema);
}

void find_file(char *path, char *target)
{
    FILE *file = fopen(path, "r");
    char line[256];
    while (fgets(line, sizeof(line), file))
        if (strstr(line, target))
            printf("%s: %s", path, line);
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
        strcpy(basepath, path);
        strcat(basepath, "/");
        strcat(basepath, entry->d_name);
        if (entry->d_type == DT_DIR)
            find_dir(basepath, target);
        if (entry->d_type == DT_REG){
            struct task buf;
            buf.is_end = 0;
            strcpy(buf.path, basepath);
            strcpy(buf.string, target);
            put_item(buf);
        }
    }
    closedir(dir);
}

void *worker_entry(void *arg)
{
    while(1) {
        struct task item = get_item();
        if (item.is_end)
            break;
        find_file(item.path, item.string);
    }
    return NULL;
}

#define WORKER_NUMBER 4
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
    if (S_ISREG(info.st_mode)){
        find_file(path, string);
        return 0;
    }

    pthread_t consumer_tid[WORKER_NUMBER];
    sema_init(&mutex_sema, 1);
    sema_init(&empty_buffer_sema, CAPACITY - 1);
    sema_init(&full_buffer_sema, 0);
    for (int i = 0; i < WORKER_NUMBER; ++i)
        pthread_create(&consumer_tid[i], NULL, worker_entry, NULL);
    find_dir(path, string);
    struct task buf;
    buf.is_end = 1;
    for (int i = 0; i < WORKER_NUMBER; ++i)
        put_item(buf);
    for (int i = 0; i < WORKER_NUMBER; ++i)
        pthread_join(consumer_tid[i], NULL);
}
```

- 先看主函数，先创建规定数量的线程，初始化信号量锁和信号量，将每个缓冲区的总容量赋值给信号量，在主线程运行消费者函数，消费者进程把缓冲区的文件路径拿出来搜索文件字符串，并互斥访问缓冲区。
- 先运行一次find_dir函数，初始化一次缓冲区，如果缓冲区未满就放入一些标识项，标记缓冲区的尾部。
- 最后等待消费者进程全部结束。
- find_dir函数获取当前路径下的目录，便利搜索，如果是文件，直接调用find_file搜索字符串，如果是文件夹，在缓冲区放入新的文件夹下的文件。

# References

[summershrimp/NUAA-OSExam: NUAA OS实验课 2016 考试题目 (github.com)](https://github.com/summershrimp/NUAA-OSExam)

[Sk-Raven/NUAA-OSLAB-2019: 南航OS实验2019 (github.com)](https://github.com/Sk-Raven/NUAA-OSLAB-2019)

[killthatshaman/NUAA_OS_EXAM: nuaa 操作系统 上机考试 (github.com)](https://github.com/killthatshaman/NUAA_OS_EXAM)