#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Passing a value to the function
void *compute(void *add);

int main() {
    pthread_t th1, th2;
    long value1 = 1;
    long value2 = 2;

    pthread_create(&th1, NULL, compute, (void*) &value1);
    pthread_create(&th2, NULL, compute, (void*) &value2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0;
}

void *compute(void *add) {
    long sum = 0;
    long *num = (long*) add;

    for (long i = 0; i < 1000000; i++) {
        sum += *num;
    }

    printf("Sum: %ld\n", sum);

    return NULL;
}

