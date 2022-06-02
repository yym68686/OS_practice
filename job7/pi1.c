#include <stdio.h>
#include <pthread.h>
#define NUMBER 1000000

double worker_output = 1;
void *worker(void *arg)
{
    for (int i = 2; i < NUMBER / 2; i++)
        worker_output += (i % 2 == 0 ? -1 : 1) * 1.0 / (2 * i - 1); 
    return NULL;
}

double master_output;
void master()
{
    for (int i = NUMBER / 2; i < NUMBER; i++)
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
    printf("master_output = %f, worker_output = %f, total = %f\n", master_output, worker_output, total);
    return 0;
}
