#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

pthread_mutex_t mutex;
pthread_cond_t condition[NUM_PHILOSOPHERS];
int state[NUM_PHILOSOPHERS];

void test(int i) 
{
    if (state[i] == HUNGRY && state[(i + 1) % NUM_PHILOSOPHERS] != EATING && state[(i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS] != EATING) 
    {
        state[i] = EATING;
        printf("Philosopher %d is eating\n", i);
        pthread_cond_signal(&condition[i]);
    }
}

void take_forks(int i) 
{
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is hungry\n", i);
    test(i);
    while (state[i] != EATING) 
    {
        pthread_cond_wait(&condition[i], &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

void put_forks(int i) 
{
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d is thinking\n", i);
    test((i + 1) % NUM_PHILOSOPHERS);
    test((i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS);
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *arg) {
    int id = *((int*)arg);
    while (1) {
        sleep(rand() % 3 + 1);
        take_forks(id);
        sleep(rand() % 3 + 1);
        put_forks(id);
    }
}

int main() 
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    
    pthread_mutex_init(&mutex, NULL);
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_cond_init(&condition[i], NULL);
        philosopher_ids[i] = i;
        state[i] = THINKING;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

