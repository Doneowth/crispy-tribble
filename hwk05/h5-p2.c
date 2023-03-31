#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>

#define DEBUG 0

long sum;
pthread_mutex_t sum_mutex;
void *runner(void *arguments); 

struct runner_args_t {
    int id; /* this is an extra field, use to describe thread id */
    long* v;
    long index;
    long size;
};

void *
runner(void *arguments) {

    struct runner_args_t *args = (struct runner_args_t *) arguments;
    if (DEBUG) printf("\n Job %d has started; index: %ld; size: %ld \n", args->id, args->index, args->size);

    long block = 0;
    for (int i = 0; i < args->size; i++) {
        block += args->v[args->index];
        args->index++;
    }
    
    // lock critical section
    pthread_mutex_lock(&sum_mutex);
    sum += block;
    pthread_mutex_unlock(&sum_mutex);
    
    // free args struct inside of runner;
    free(args);

    if (DEBUG) printf("\n Job %d has finished, Block Sum: %ld \n\n", args->id, block);
}

int
main(int argc, char *argv[]) { 
    
    // Calc time performance time
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    // parameter check & instruction popup 
    if (argc != 3) {
        fprintf(stderr, "usage: ./h5-p2 <num_elements> <num_threads>\n");
        exit(1);
    }

    // get 
    int num_elements = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    long v[num_elements];
    
    long start_ind = 0;
    long step = num_elements / num_threads;

    // Dynamic allocate, initialize vector v
    for (int i = 0; i < num_elements; i++)
        v[i] = i;

    // create thread array
    pthread_t *slave_thread = malloc(sizeof(pthread_t) * num_threads);

    // create threads
    for (int i = 0; i < num_threads; i++) {
        struct runner_args_t *args = malloc(sizeof(struct runner_args_t));
        args->id = i;
        args->v = v;
        args->index = start_ind;
        args->size = step;

        // merge extra elements into last thread
        if (i == num_threads - 1 && start_ind + step < num_elements)
            args->size =num_elements - start_ind;        
        
        // make sure the workload is evenly deistibuted
        start_ind += step;
        pthread_create(&slave_thread[i], NULL, runner, args);   
    }
    
    // join threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(slave_thread[i], NULL);
    }

    // free thread array & thread's arguments structure
    free(slave_thread);

    printf("Sum = %ld \n\n", sum);
    gettimeofday(&stop, NULL);
    printf("Took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
    return EXIT_SUCCESS;
}