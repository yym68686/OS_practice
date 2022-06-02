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
