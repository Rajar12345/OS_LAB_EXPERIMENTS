/*QUESTION: Create a C program to fork two user threads namely, T1 and T2.
T1 prints its thread id and has to wait for a random amount of time before it can resume its execution. 
T2 prints its thread id and waits till T1 is ready to join. 
T1 resumes its operation and performs one system call and one user-defined function call.
 Both the calls are timed and displayed on the screen. After display, T1 and T2 joins and exits.*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void user_defined_function() {
for (int i = 0; i < 1000000; ++i) {
        // Simulate some work
    }
}
void *thread1_function(void *arg) {
    printf("T1 Thread ID: %lu\n", pthread_self());

    int wait_time = rand() % 5 + 1;
    printf("T1 is waiting for %d seconds\n", wait_time);
    sleep(wait_time);

    printf("T1 resumes execution\n");

    printf("T1: Performing system call\n");
    getpid();

    printf("T1: Calling user-defined function\n");
    user_defined_function();

    pthread_exit(NULL);
}
void *thread2_function(void *arg) {
    printf("T2 Thread ID: %lu\n", pthread_self());
    pthread_join(*(pthread_t *)arg, NULL);
    printf("T2 joins after T1\n");
    pthread_exit(NULL);
}
int main() {
    pthread_t t1, t2;

    srand(time(NULL));

    pthread_create(&t1, NULL, thread1_function, NULL);
    pthread_create(&t2, NULL, thread2_function, &t1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

