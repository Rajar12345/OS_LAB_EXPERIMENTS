#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) 
{
    int item;
    for (int i = 0; i < 10; i++) 
    {
        item = rand() % 100; 
        sem_wait(&empty); 
        pthread_mutex_lock(&mutex); 
        printf("Producing %d\n", item);
        buffer[i % BUFFER_SIZE] = item;
        pthread_mutex_unlock(&mutex); 
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) 
{
    int item;
    for (int i = 0; i < 10; i++) 
    {
        sem_wait(&full); 
        pthread_mutex_lock(&mutex); 
        item = buffer[i % BUFFER_SIZE];
        printf("Consuming %d\n", item);
        pthread_mutex_unlock(&mutex); 
        sem_post(&empty); 
    }
    pthread_exit(NULL);
}
int main() 
{
    pthread_t prod_thread, cons_thread;
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}

