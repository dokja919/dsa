#include "circular_queue.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 8

struct CircularQueue {
    CItem *items;
    size_t capacity;
    size_t front;
    size_t size;
};

CQueue *c_create(void)
{
    CQueue *queue = malloc(sizeof(*queue));
    if (queue == NULL) {
        return NULL;
    }

    queue->capacity = INITIAL_CAPACITY;
    queue->items = malloc(sizeof(*queue->items) * queue->capacity);
    if (queue->items == NULL) {
        free(queue);
        return NULL;
    }
    queue->front = 0;
    queue->size = 0;

    return queue;
}
void c_destroy(CQueue *queue)
{
    if (queue == NULL) {
        return;
    }
    free(queue->items);
    free(queue);
}
void c_enqueue(CQueue *queue, int value)
{
    if (queue == NULL) {
        return;
    }
    if (queue->size == queue->capacity) {
        size_t new_capacity = queue->capacity * 2;
        CItem *new_items = malloc(sizeof(*new_items) * new_capacity);
        if (new_items == NULL) {
            return;
        }
        for (size_t i = 0; i < queue->size; i++) {
            size_t j = (queue->front + i) % queue->capacity;
            new_items[i] = queue->items[j];
        }
        free(queue->items);
        queue->items = new_items;
        queue->capacity = new_capacity;
        queue->front = 0;
    }
    size_t rear = (queue->front + queue->size) % queue->capacity;
    queue->items[rear] = value;
    queue->size++;
}
CItem c_dequeue(CQueue *queue)
{
    if (c_is_empty(queue)) {
        return 0;
    }
    CItem data = queue->items[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return data;
}
CItem c_peek(CQueue *queue)
{
    if (c_is_empty(queue)) {
        return 0;
    }
    return queue->items[queue->front];
}
bool c_is_empty(CQueue *queue)
{
    return queue == NULL || queue->size == 0;
}
size_t c_size(CQueue *queue)
{
    return queue ? queue->size : 0;
}