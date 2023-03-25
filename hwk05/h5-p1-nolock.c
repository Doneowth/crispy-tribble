#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

typedef struct __node_t {
    int value;
    struct __node_t *next;
} node_t;

typedef struct __queue_t {
    node_t *head;
    node_t *tail;
    pthread_mutex_t head_lock, tail_lock;
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
    // pthread_mutex_init(&q->head_lock, NULL);
    // pthread_mutex_init(&q->tail_lock, NULL);
}

void 
*Queue_Enqueue(void *arguments) {
    struct arg_struct_enq *args = (struct arg_struct_enq *) arguments;
    node_t *tmp = malloc(sizeof(node_t));
    assert(tmp != NULL);
    tmp->value = args->val; 
    tmp->next = NULL;
    // pthread_mutex_lock(&q->tail_lock);
    args->q->tail->next = tmp;
    args->q->tail = tmp;// tail always points to the last enqueued node or
    // to the dummy node (if the queue is empty)
    // pthread_mutex_unlock(&q->tail_lock);
}

int 
*Queue_Dequeue(void *arguments) {
    struct arg_struct_deq *args = (struct arg_struct_deq *) arguments;

    // pthread_mutex_lock(&q->head_lock);
    node_t *tmp = args->q->head; 
    node_t *new_head = tmp->next;
    if (new_head == NULL) {// indicates an empty queue with only a dummy node
        // pthread_mutex_unlock(&q->head_lock);
        printf("Not enough elements\n");
        args->val = -1;
        return -1; 
    }
    args->val = new_head->value;
    args->q->head = new_head; //head always points to a dummy node,
    //which is either the original dummy node or most recently dequeued node
    // pthread_mutex_unlock(&q->head_lock);
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
    // test q initialization
    queue_t q;
    Queue_Init(&q);

    // create 3 enqueue thread
    pthread_t enq_p0, enq_p1, enq_p2;
    printf("main: begin\n");
    struct arg_struct_enq args0;
    args0.q = &q;
    args0.val = 1;
    
    struct arg_struct_enq args1;
    args1.q = &q;
    args1.val = 5;

    struct arg_struct_enq args2;
    args2.q = &q;
    args2.val = 6;

    // create 2 dequeue thread
    pthread_t deq_p1, deq_p2;
    struct arg_struct_deq args3;
    args3.q = &q;

    struct arg_struct_deq args4;
    args4.q = &q;

    pthread_create(&enq_p0, NULL, &Queue_Enqueue, &args0); 
    pthread_create(&enq_p1, NULL, &Queue_Enqueue, &args1); 
    pthread_create(&enq_p2, NULL, &Queue_Enqueue, &args2);

    pthread_create(&deq_p1, NULL, &Queue_Dequeue, &args3); 
    pthread_create(&deq_p2, NULL, &Queue_Dequeue, &args4);
    
    // join waits for the threads to finish
    pthread_join(enq_p0, NULL); 
    pthread_join(enq_p1, NULL); 
    pthread_join(enq_p2, NULL); 
    pthread_join(deq_p1, NULL); 
    pthread_join(deq_p2, NULL);
    Queue_Display(&q);

    printf("main: end\n");
    return 0;
}