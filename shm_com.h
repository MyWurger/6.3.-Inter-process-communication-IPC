#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H
#include <pthread.h>

#define SHM_SIZE 4096
struct shared_data_original
{
    char data[SHM_SIZE];
};

struct shared_data_code
{
    char data[SHM_SIZE];
};

extern pthread_mutex_t mutex;

#endif