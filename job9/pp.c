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
