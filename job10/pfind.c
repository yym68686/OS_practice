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
