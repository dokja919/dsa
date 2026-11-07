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
    heap->capacity = INITIAL_CAPACITY;
    heap->items = malloc(sizeof(BItem) * heap->capacity);
    if (heap->items == NULL) {
        free(heap);
        return NULL;
    }
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
static bool ensure_capacity(BPriorityQueue* heap)
{
    if (heap == NULL) {
        return false;
    }
    if (heap->size < heap->capacity) {
        return true;
    }
    size_t new_capacity = heap->capacity * 2;

    BItem* new_items = realloc(heap->items, sizeof(*new_items) * new_capacity);
    if (new_items == NULL) {
        return false;
    }
    heap->items = new_items;
    heap->capacity = new_capacity;

    return true;
}
bool b_push(BPriorityQueue* heap, BItem data)
{
    if (heap == NULL) {
        return false;
    }
    if (ensure_capacity(heap) == false) {
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
bool b_peek(BPriorityQueue* heap, BItem* out_data)
{
    if (heap == NULL || heap->size == 0) {
        return false;
    }
    *out_data = heap->items[0];

    return true;
}
static void heapify(BPriorityQueue* heap, size_t parent)
{
    size_t left = 2 * parent + 1;
    if (left >= heap->size) {
        return;
    }
    size_t right = left + 1;
    size_t child = left;

    if (right < heap->size && heap->items[right].priority > heap->items[left].priority) {
        child = right;
    }
    if (heap->items[parent].priority >= heap->items[child].priority) {
        return;
    }
    BItem temp = heap->items[parent];
    heap->items[parent] = heap->items[child];
    heap->items[child] = temp;

    heapify(heap, child);
}
bool b_pop(BPriorityQueue* heap, BItem* out_data)
{
    if (heap == NULL || heap->size == 0) {
        return false;
    }
    if (out_data != NULL) {
        *out_data = heap->items[0];
    }
    heap->size--;

    if (heap->size > 0) {
        heap->items[0] = heap->items[heap->size];
        heapify(heap, 0);
    }
    return true;
}
bool b_is_empty(BPriorityQueue* heap)
{
    return heap == NULL || heap->size == 0;
}
size_t b_size(BPriorityQueue* heap)
{
    return heap ? heap->size : 0;
}