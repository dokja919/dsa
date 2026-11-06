#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int priority;
} BItem;
typedef struct BinaryHeap BPriorityQueue;

BPriorityQueue* b_create(void);
void b_destroy(BPriorityQueue* heap);
bool b_push(BPriorityQueue* heap, BItem data);
int b_pop(BPriorityQueue* heap);
size_t b_size(BPriorityQueue* heap);
bool b_is_empty(BPriorityQueue* heap);

#endif