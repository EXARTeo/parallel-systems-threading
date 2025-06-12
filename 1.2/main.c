#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../parallel-systems-handout-1-winter-2024-25-helpcode/my_rand.h"
#include "../parallel-systems-handout-1-winter-2024-25-helpcode/timer.h"



// Global shared variables
long long int loops_per_thread, thread_count, sum;

pthread_mutex_t my_mutex;

// Function prototypes
void *Thread_sum_mutex();
void *Thread_sum_atomic();

int main(int argc, char *argv[]) {
    long long int thread;
    pthread_t *thread_handles;

    // get total tosses and thread count from terminal arguments
    loops_per_thread = strtol(argv[1], NULL, 10);
    thread_count = strtol(argv[2], NULL, 10);

    thread_handles = malloc(thread_count * sizeof(pthread_t));

    double start_time, end_time;

    // Mutex-lock implementation
    sum = 0;
    pthread_mutex_init(&my_mutex, NULL);

    GET_TIME(start_time);

    for (thread = 0; thread < thread_count; thread++){
        if(pthread_create(&thread_handles[thread], NULL, Thread_sum_mutex, NULL) != 0){
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    GET_TIME(end_time);

    printf("====== Mutex-lock implementation ======\n");
    printf("== Total sum from all threads : %lld\n", sum);
    printf("== Time: %f\n", end_time - start_time);
    printf("=======================================\n\n");

    pthread_mutex_destroy(&my_mutex);


    // Atomic-lock implementation
    sum = 0;
    GET_TIME(start_time);

    for (thread = 0; thread < thread_count; thread++){
        if(pthread_create(&thread_handles[thread], NULL, Thread_sum_atomic, NULL) != 0){
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    GET_TIME(end_time);

    printf("====== Atomic-lock implementation ======\n");
    printf("== Total sum from all threads : %lld\n", sum);
    printf("== Time: %f\n", end_time - start_time);
    printf("=======================================\n\n");

    free(thread_handles);

    return 0;

}

void *Thread_sum_mutex() {
    for (long long int i = 0; i < loops_per_thread; i++) {
        // Lock all other threads out ..
        pthread_mutex_lock(&my_mutex);
        sum ++;                     // ..every time one thread wants to add 1 to the sum
        pthread_mutex_unlock(&my_mutex);
    }
    return NULL;
}

void *Thread_sum_atomic() {
    for (long long int i = 0; i < loops_per_thread; i++)
        // Using atomic add, to increment the sum value
        __atomic_fetch_add(&sum, (long long int)1, __ATOMIC_RELAXED);
    return NULL;
}