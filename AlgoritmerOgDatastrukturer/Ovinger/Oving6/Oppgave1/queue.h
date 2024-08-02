#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    void** table;
    int start, end, amount, max;
} Queue;

Queue* new_queue(int size) {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->table = (void*) (malloc(size * sizeof(void*)));
    q->max = size;
    q->start = q->end = q->amount = 0;
    return q;
}

bool empty_queue_check(Queue* q) {
    return !q->amount;
}

bool full_queue(Queue* q) {
    return q->amount == q->max;
}

void add_to_queue(Queue* q, void* e) {
    if (full_queue(q)) {
        printf("The queue is full! Could not add the item to the queue!\n");
        return;
    }
    q->table[q->end] = e;
    q->end = (q->end + 1) % q->max;
    ++q->amount;
}

void* next_in_queue(Queue* q) {
    void* e;
    if (empty_queue_check(q)) return NULL;
    e = q->table[q->start];
    q->start = (q->start + 1) % q->max;
    --q->amount;
    return e;
}

void* check_queue(Queue* q) {
    if (empty_queue_check(q)) return NULL;
    return q->table[q->start];
}

