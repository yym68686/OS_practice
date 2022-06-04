// + 补全生产者、计算者、消费者程序
//   - 完成函数 buffer_init
//   - 完成函数 buffer_get
//   - 完成函数 buffer_put
//   - 补全函数 main
//     * 创建生产者、计算者、消费者
//
// + 程序最终输出
//   - 生产者输出 a b c d e f g h
//   - 消费者输出 A B C D E F G H
//   - 消费者输出 A B C D E F G H
//   - 两者交叉输出 
//
// + 不准对函数 produce 、函数 compute、 函数 consume 进行任何改动
//   - 如果改动，则该题没有分数
//
// + 本题对 buffer 进行了抽象和封装
//   - buffer_pc 连接 producer 和 computer
//   - buffer_cc 连接 computer 和 consumer 

#include <stdio.h>
#include <pthread.h>
#include <ctype.h>

#define CAPACITY 4      // 缓冲区的最大容量

struct buffer {
    int data[CAPACITY];
    int in;             // 缓冲区的写指针
    int out;            // 缓冲区的读指针
    pthread_mutex_t mutex;
    pthread_cond_t wait_empty_buffer;
    pthread_cond_t wait_full_buffer;
};

// 初始化 buffer，需要初始化用于同步的字段 
void buffer_init(struct buffer *buffer)
{
    buffer->in = 0;
    buffer->out = 0;
	pthread_mutex_init(&buffer->mutex, NULL);
	pthread_cond_init(&buffer->wait_empty_buffer, NULL);
	pthread_cond_init(&buffer->wait_full_buffer, NULL);
}

// 判断缓冲区是否为空
int buffer_is_empty(struct buffer *buffer)
{
    return buffer->in == buffer->out;
}

// 判断缓冲区是否为满
int buffer_is_full(struct buffer *buffer)
{
    return (buffer->in + 1) % CAPACITY == buffer->out;
}

// 向缓冲区中追加一个数据，如果缓冲区为满，则等待
void buffer_put(struct buffer *buffer, int item)
{
	pthread_mutex_lock(&buffer->mutex);
	while (buffer_is_full(buffer))
		pthread_cond_wait(&buffer->wait_empty_buffer, &buffer->mutex);
	buffer->data[buffer->in] = item;
	buffer->in = (buffer->in + 1) % CAPACITY;
	pthread_cond_signal(&buffer->wait_full_buffer);
	pthread_mutex_unlock(&buffer->mutex);
}

// 从缓冲区中取走一个数据，如果缓冲区为空，则等待
int buffer_get(struct buffer *buffer)
{
	pthread_mutex_lock(&buffer->mutex);
	while (buffer_is_empty(buffer))
		pthread_cond_wait(&buffer->wait_full_buffer, &buffer->mutex);
	int item;
	item = buffer->data[buffer->out];
	buffer->out = (buffer->out + 1) % CAPACITY;
	pthread_cond_signal(&buffer->wait_empty_buffer);
	pthread_mutex_unlock(&buffer->mutex);
	return item;
}

#define ITEM_COUNT (2 * CAPACITY)

struct buffer buffer_pc, buffer_cc;

void *produce(void *arg)
{
    int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) { 
        item = 'a' + i;
        printf("produce item: %c\n", item);
        buffer_put(&buffer_pc, item);
    }
    return NULL;
}

void *compute(void *arg)
{
    int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) { 
        item = buffer_get(&buffer_pc); 
        item = toupper(item);
        printf("    compute item: %c\n", item); 
        buffer_put(&buffer_cc, item);
    }
    return NULL;
}

void *consume(void *arg)
{
    int i;
    int item;

    for (i = 0; i < ITEM_COUNT; i++) { 
        item = buffer_get(&buffer_cc); 
        printf("        consume item: %c\n", item); 
    }
    return NULL;
}

int main()
{ 
    buffer_init(&buffer_pc);
    buffer_init(&buffer_cc);

    pthread_t producer_tid;
    pthread_t computer_tid;
    pthread_t consumer_tid;

    
    pthread_create(&producer_tid, NULL, produce, NULL);
    pthread_create(&computer_tid, NULL, compute, NULL);
    pthread_create(&consumer_tid, NULL, consume, NULL);
    pthread_join(consumer_tid, NULL);

    return 0;
}
