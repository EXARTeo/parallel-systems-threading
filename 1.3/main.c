#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../parallel-systems-handout-1-winter-2024-25-helpcode/my_rand.h"
#include "../parallel-systems-handout-1-winter-2024-25-helpcode/timer.h"

long long int total_loops, thread_count;

// Global shared variables
long long int *sum;

void *Thread_sum(void *rank);

int main(int argc, char *argv[])
{
    long long int thread, i;
    pthread_t *thread_handles;

    // get total tosses and thread count from terminal arguments
    total_loops = strtol(argv[1], NULL, 10);
    thread_count = strtol(argv[2], NULL, 10);

    thread_handles = malloc(thread_count * sizeof(pthread_t));

    double start_time, end_time;

    // allocate memory for the shared array
    // initialize the array to 0
    sum = malloc(sizeof(long long int) * thread_count);
    for (i = 0; i < thread_count; i++)
        sum[i] = 0;

    GET_TIME(start_time);
    for (thread = 0; thread < thread_count; thread++)
    {
        if (pthread_create(&thread_handles[thread], NULL, Thread_sum, (void *)thread) != 0)
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    GET_TIME(end_time);

    // Get the total sum from all threads' sums
    long long int big_sum = 0;
    for (i = 0; i < thread_count; i++)
        big_sum += sum[i];

    printf("====== Implementation ======\n");
    printf("==== Sum of each thread ====\n");
    for (i = 0; i < thread_count; i++)
        printf("== sum[%lld] = %lld\n", i, sum[i]);
    printf("==  Total sum from all threads : %lld\n", big_sum);
    printf("==  Time: %f\n", end_time - start_time);
    printf("=======================================\n\n");

    free(thread_handles);
    free(sum);

    return 0;
}

void *Thread_sum(void *rank)
{
    long long int my_rank = (long long int)rank;
    long long int loops_per_thread;

    loops_per_thread = total_loops / thread_count;
    long long int moded_loops = total_loops % thread_count;       // Remaining loops

    // Distribute the remainder to the first 'moded_loops' threads
    if (my_rank < moded_loops) {
        loops_per_thread++;
    }

    for (long long int i = 0; i < loops_per_thread; i++)
        // Adding 1 only to the cell that is parallel to the rank of the thread
        sum[my_rank]++;

    return NULL;
}