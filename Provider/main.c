#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include "shm_com.h"


#define SEGMENT_SIZE SHM_SIZE
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void print_shared_memory(struct shared_data_original *data, int segment_half) 
{
    pthread_mutex_lock(&mutex);
    if(segment_half==1)
    {
        printf("Исходный рабочий файл:\n");
    }
    else if(segment_half==2)
    {
        printf("Файл со случайной шифрующей последовательностью:\n");
    }
    printf("Указатель на сегмент %i разделяемой памяти в дочерней программе: %p\n", segment_half, (void *)data);
    printf("Прочитанные данные: %s\n", data->data);
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[]) 
{
    if (argc != 4) 
    {
        fprintf(stderr, "Использование: %s <название файла> <ключ> <номер половинки>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    key_t key = atoi(argv[2]);
    int segment_half = atoi(argv[3]);

    int shmid = shmget(key + segment_half, SEGMENT_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget провалилась");
        exit(EXIT_FAILURE);
    }

    struct shared_data_original *data = (struct shared_data_original *)shmat(shmid, NULL, 0);
    if (data == (struct shared_data_original *)(-1)) 
    {
        perror("shmat провалилась");
        exit(EXIT_FAILURE);
    }


    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Не удалось открыть файл %s\n", argv[1]);
        shmdt((void *)data);
        exit(EXIT_FAILURE);
    }

    // Читаем данные из файла в разделяемую память
    fread(data->data, 1, SHM_SIZE, file);

    fclose(file);
    print_shared_memory(data, segment_half);

    // Отключение сегмента разделяемой памяти
    if (shmdt((void *)data) == -1) {
        perror("shmdt не выполнилась");
        exit(EXIT_FAILURE);
    }

    return 0;
}