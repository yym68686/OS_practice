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
