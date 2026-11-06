#include "binary_heap.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 8 // 16

struct BinaryHeap {
    BItem* items;
    size_t capacity;
    size_t size;
};

BPriorityQueue* b_create(void)
{
    BPriorityQueue* heap = malloc(sizeof(*heap));
    if (heap == NULL) {
        return NULL;
    }
    size_t capacity = INITIAL_CAPACITY;

    heap->items = malloc(sizeof(BItem) * capacity);
    if (heap->items == NULL) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;

    return heap;
}
void b_destroy(BPriorityQueue* heap)
{
    if (heap == NULL) {
        return;
    }
    free(heap->items);
    free(heap);
}
bool b_push(BPriorityQueue* heap, BItem data)
{
    if (heap == NULL) {
        return false;
    }
    size_t index = heap->size;

    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (data.priority <= heap->items[parent].priority) {
            break;
        }
        heap->items[index] = heap->items[parent];
        index = parent;
    }
    heap->items[index] = data;
    heap->size++;

    return true;
}
int b_pop(BPriorityQueue* heap)
{
    int top = 0;

    if (heap == NULL || heap->size == 0) {
        return top;
    }
    top = heap->items[0].priority;
    heap->size--;

    if (heap->size > 0) {
        heap->items[0] = heap->items[heap->size];
        b_heapify(heap->items, heap->size, 0);
    }
    return top;
}
static void b_heapify(BItem* items, size_t size, size_t parent)
{
    size_t left = 2 * parent + 1;
    if (left >= size) {
        return;
    }

    size_t right = left + 1;
    size_t child = left;

    if (right < size &&
        items[right].priority > items[left].priority) {
        child = right;
    }

    if (items[parent].priority >= items[child].priority) {
        return;
    }

    BItem temp = items[parent];
    items[parent] = items[child];
    items[child] = temp;

    b_heapify(items, size, child);
}
bool b_is_empty(BPriorityQueue* heap)
{
    return heap == NULL || heap->size == 0;
}
size_t b_size(BPriorityQueue* heap)
{
    return heap ? heap->size : 0;
}