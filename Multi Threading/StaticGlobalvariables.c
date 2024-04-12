#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int a = 0;

void *func(void *var) {
    int *id = (int *)var;
    static int b = 0;
    b = 7;
    a = 7;
    
    printf("The id of the thread: %d\n", *id);
    printf("The value of static variable: %d\n", b);
    printf("The value of global variable: %d\n", a);
    
    pthread_exit(NULL);  // Explicitly exit the thread
}

int main() {
    pthread_t th_id;
    
    for (int i = 0; i < 9; i++) {
        pthread_create(&th_id, NULL, func, (void *)&th_id);
        pthread_join(th_id, NULL);  // Wait for the thread to finish before creating the next one
    }

    return 0;
}

