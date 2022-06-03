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
