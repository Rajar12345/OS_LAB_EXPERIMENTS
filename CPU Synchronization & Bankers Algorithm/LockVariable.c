#include <stdio.h>
#include <pthread.h>
pthread_mutex_t lock;
void* thread_function(void* arg) 
{
    pthread_mutex_lock(&lock);
    printf("Thread %ld is in the critical section.\n", (long)arg);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() 
{
    pthread_t threads[5];
    long i;
    pthread_mutex_init(&lock, NULL);
    for (i = 0; i < 5; i++) 
    {
        if (pthread_create(&threads[i], NULL, thread_function, (void*)i) != 0) 
        {
            perror("pthread_create");
            return 1;
        }
    }
    for (i = 0; i < 5; i++) 
    {
        if (pthread_join(threads[i], NULL) != 0) 
        {
            perror("pthread_join");
            return 1;
        }
    }
    pthread_mutex_destroy(&lock);
    return 0;
}

