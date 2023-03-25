#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>

#define MAX_THREADS_NUM 10000

typedef struct __node_t {
    int value;
    struct __node_t *next;
} node_t;

typedef struct __queue_t {
    node_t *head;
    node_t *tail;
    // pthread_mutex_t head_lock, tail_lock;
    pthread_mutex_t one_lock;

} queue_t;

struct arg_struct_enq {
    queue_t *q;
    int val;
};

struct arg_struct_deq {
    queue_t *q;
    int* val;
};

void 
Queue_Init(queue_t *q) {
    //Creating the dummy node, which is needed so that “tail” update is separated from “head” update.
    node_t *tmp = malloc(sizeof(node_t));
    tmp->next = NULL; //a dummy node has next=NULL and no need to set its value attribute
    q->head = q->tail = tmp;
    // only init one_lock
    pthread_mutex_init(&q->one_lock, NULL);
    // pthread_mutex_init(&q->tail_lock, NULL);
}

void 
*Queue_Enqueue(void *arguments) {
    struct arg_struct_enq *args = (struct arg_struct_enq *) arguments;
    node_t *tmp = malloc(sizeof(node_t));
    assert(tmp != NULL);
    tmp->value = args->val; 
    tmp->next = NULL;
    pthread_mutex_lock(&args->q->one_lock);
    args->q->tail->next = tmp;
    args->q->tail = tmp;// tail always points to the last enqueued node or
    // to the dummy node (if the queue is empty)
    pthread_mutex_unlock(&args->q->one_lock);
}

int 
*Queue_Dequeue(void *arguments) {
    struct arg_struct_deq *args = (struct arg_struct_deq *) arguments;

    pthread_mutex_lock(&args->q->one_lock);
    node_t *tmp = args->q->head; 
    node_t *new_head = tmp->next;
    if (new_head == NULL) {// indicates an empty queue with only a dummy node
        pthread_mutex_unlock(&args->q->one_lock);
        printf("Not enough elements\n");
        args->val = -1;
        return -1; 
    }
    args->val = new_head->value;
    args->q->head = new_head; //head always points to a dummy node,
    //which is either the original dummy node or most recently dequeued node
    pthread_mutex_unlock(&args->q->one_lock);
    free(tmp); // old dummy node is removed
    return 0; 
}

void
Queue_Display(queue_t *q) 
{
    printf("Queue elements: \n");
    node_t *ptr = q->head->next;
    while (ptr != NULL) {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }
    printf("\n\n");
}

int 
main(int argc, char *argv[]) {
    // calc time performance time
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    // test q initialization
    queue_t q;
    Queue_Init(&q);

     pthread_t enq_thread[MAX_THREADS_NUM];
    struct arg_struct_enq args1[MAX_THREADS_NUM];

    // create 10 000 threads to enque;
    for (int i = 0; i < MAX_THREADS_NUM; i++) {
        args1[i].q = &q;
        args1[i].val = 5;
        pthread_create(&enq_thread[i], NULL, &Queue_Enqueue, &args1[i]);   
    }

    for (int i = 0; i < MAX_THREADS_NUM; i++) {
        pthread_join(enq_thread[i], NULL);   
    }

    // create 10 000 threads to deque;
    pthread_t deq_thread[MAX_THREADS_NUM];
    struct arg_struct_deq args2[MAX_THREADS_NUM];
    // create 10 000 threads to enque;
    for (int i = 0; i < MAX_THREADS_NUM; i++) {
        args2[i].q = &q;
        pthread_create(&deq_thread[i], NULL, &Queue_Dequeue, &args2);   
    }
    for (int i = 0; i < MAX_THREADS_NUM; i++) {
        pthread_join(deq_thread[i], NULL);   
    }

    Queue_Display(&q);

    printf("main: end\n");
    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 


    return 0;
}