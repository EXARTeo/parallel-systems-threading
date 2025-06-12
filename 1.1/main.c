#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../parallel-systems-handout-1-winter-2024-25-helpcode/my_rand.h"
#include "../parallel-systems-handout-1-winter-2024-25-helpcode/timer.h"

int thread_count;
long long int total_tosses, sum = 0;
pthread_mutex_t my_mutex;

void *Thread_pi(void *rank);

int main(int argc, char *argv[]) {
    long long int thread;
    pthread_t *thread_handles;

    // get total tosses and thread count from terminal arguments
    total_tosses = strtol(argv[1], NULL, 10);
    thread_count = strtol(argv[2], NULL, 10);
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    // ordinal algorithm
    unsigned int seed = 20000;
    double ordinal_time, parallel_time;
    double x, y, square_dist;
    double start_time, end_time;

    long long int circle_arrows = 0;
    long long int toss;

    GET_TIME(start_time);
    for (toss = 0; toss < total_tosses; toss++) {
        x = my_drand(&seed);
        y = my_drand(&seed);
        square_dist = x * x + y * y;
        // if it hit the circle..
        if (square_dist <= 1)
            circle_arrows++;    // ..add +1 to the total sum
    }
    GET_TIME(end_time);

    ordinal_time = end_time - start_time;

    double pi_estimate = 4 * circle_arrows / (double)total_tosses;

    printf("pi estimation (ordinal algorithm): %f\n", pi_estimate);
    printf("Time: %f\n", ordinal_time);

    // parallel algorithm
    pthread_mutex_init(&my_mutex, NULL);
    GET_TIME(start_time)

    for (thread = 0; thread < thread_count; thread++) {
        if(pthread_create(&thread_handles[thread], NULL, Thread_pi, (void *)thread) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    pi_estimate = 4 * sum / (double)total_tosses;
    GET_TIME(end_time);
    parallel_time = end_time - start_time;
    printf("pi estimation (parallel algorithm): %f\n", pi_estimate);
    printf("Time: %f\n", parallel_time);

    free(thread_handles);
    pthread_mutex_destroy(&my_mutex);
    return 0;
}

void *Thread_pi(void *rank) {
    long my_rank = (long)rank;
    double x, y, square_dist;
    long long int my_n = total_tosses / thread_count;
    long long int my_first_i = my_n * my_rank;
    long long int my_last_i = my_first_i + my_n;

    // If we cannot distribute equally the tosses..
    // ..give just a few more to the first thread
    if (my_rank == thread_count - 1)
        my_last_i = total_tosses;

    unsigned int parallel_seed = 10000;

    long long int circle_arrows = 0;
    
    // Calculate the tosses for this thread 
    for (long long int i = my_first_i; i < my_last_i; i++) {
        x = my_drand(&parallel_seed);
        y = my_drand(&parallel_seed);
        square_dist = x * x + y * y;
        if (square_dist <= 1)
            circle_arrows++;
    }

    // Make sure no more than one thread..
    // ..try to write on shared variable sum
    pthread_mutex_lock(&my_mutex);
    sum += circle_arrows;
    pthread_mutex_unlock(&my_mutex);
    return NULL;
}