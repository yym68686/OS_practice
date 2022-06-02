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
