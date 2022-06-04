// + 实现函数 list_visit
//   - 主程序遍历链表 list 的每个节点
//   - 对每个节点创建一个子线程，在这道题目中，总共创建 7 个子线程
//   - 在每个子线程中，打印 node->data
//
// + 实现函数 wait_sub_threads
//   - 等待所有的子线程执行完毕
//   - 在 list_visit 时，需要记录下所有线程的 ID，记录在全局变量中
//   - 在 wait_sub_threads 中使用 pthread_join
//
// + 程序可能的输出结果
//   - 字符 a b c d e f g 每个出现一次，出现的顺序可能是随机的  
//   - END 一定是最后出现
//   a
//   d
//   b
//   e
//   c
//   f
//   g
//   END
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct node {
    char data;
    struct node *next;
};

pthread_t workers[7];

struct node *node_create(char data)
{
    struct node *node = malloc(sizeof(struct node));
    node->data = data;
    node->next = NULL;
    return node;
}


void list_visit(struct node *list)
{

}

// 遍历算法，供参考
void list_print(struct node *list)
{
    struct node *node = list;
    while (node) {
        printf("%c\n", node->data);
        node = node->next;
    }
}

void wait_sub_threads()
{
	for (int i = 0; i < 7; i++)
		pthread_join(worker[i], NULL);
}

int main()
{
    struct node *list = NULL;
    for (char data = 'g'; data >= 'a'; data--) {
        struct node *node = node_create(data);
        node->next = list;
        list = node;
    }

    list_print(list);
    wait_sub_threads();

    puts("END");
    return 0;
}
