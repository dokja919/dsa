#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stddef.h>

typedef struct BItem BItem;
typedef struct BinaryHeap BPriorityQueue;

BPriorityQueue* b_create(void);
void b_destroy(BPriorityQueue* heap);
void b_push(BPriorityQueue* heap, int priority);
int b_pop(BPriorityQueue* heap);
size_t b_size(BPriorityQueue* heap);
int b_is_empty(BPriorityQueue* heap);
void b_heapify(BItem* items, size_t size, size_t parent);

#endif