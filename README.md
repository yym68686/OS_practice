# 2022南航计算机学院操作系统课程的实验代码

文档：

[基本I/O系统调用](https://www.linuxmooc.com/courses/io/)

[文件描述符](https://www.linuxmooc.com/courses/fd/)

[进程管理](https://www.linuxmooc.com/courses/proc/)

文件读写编程题目

## job3/myecho.c

myecho.c的功能与系统echo程序相同

接受命令行参数，并将参数打印出来，例子如下：

```
$ ./myecho x
x
$ ./myecho a b c
a b c
```

## job3/mycat.c
mycat.c的功能与系统cat程序相同
mycat将指定的文件内容输出到屏幕，例子如下：
要求使用系统调用open/read/write/close实现

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

## job3/mycp.c
mycp.c的功能与系统cp程序相同

将源文件复制到目标文件，例子如下：

要求使用系统调用open/read/write/close实现

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

多进程题目

## job3/mysys.c

实现函数mysys，用于执行一个系统命令，要求如下

mysys的功能与系统函数system相同，要求用进程管理相关系统调用自己实现一遍

使用fork/exec/wait系统调用实现mysys

不能通过调用系统函数system实现mysys

测试程序
```
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
测试程序的输出结果
--------------------------------------------------
HELLO WORLD
--------------------------------------------------
bin    core  home	     lib	 mnt   root  snap  tmp	vmlinuz
boot   dev   initrd.img      lost+found  opt   run   srv   usr	vmlinuz.old
cdrom  etc   initrd.img.old  media	 proc  sbin  sys   var
--------------------------------------------------
```

## job3/sh1.c

该程序读取用户输入的命令，调用函数mysys(上一个作业)执行用户的命令，示例如下

### 编译sh1.c

```
$ cc -o sh1 sh1.c
```

### 执行sh1

```
$ ./sh 
```

### sh1打印提示符>，同时读取用户输入的命令echo，并执行输出结果

```
echo a b c
a b c
```

### sh1打印提示符>，同时读取用户输入的命令cat，并执行输出结果

```
cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
```

实现内置命令cd、pwd、exit

参考链接：
[基本I/O系统调用](https://www.cnblogs.com/QG-whz/p/5469891.html)


## job4/myls.c

myls.c的功能与系统ls程序相同

opendir readdir closedir

在命令行中输入 man opendir 获取帮助

列出指定目录下的文件，例子如下：

```
$ ./myls job4/test
a
b
c
```

列出当前目录下的文件，例子如下：

```
$ cd job4/test 
$ ./myls
a
b
c
```

## job4/mytree.c

mytree.c的功能与系统tree程序相同

使用空格作为缩进，表示层次

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

## job5/sh2.c
实现shell程序，要求在第1版的基础上，增加文件重定向功能

- 重定向输入
- 重定向输出
- 重定向追加

References

[Linux Shell 输入重定向](http://c.biancheng.net/view/942.html)

[Shell 输入/输出重定向](https://www.runoob.com/linux/linux-shell-io-redirections.html)
