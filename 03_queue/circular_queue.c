#include "circular_queue.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 8 // 16

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
bool c_enqueue(CQueue *queue, CItem data)
{
    if (queue == NULL) {
        return false;
    }
    if (queue->size == queue->capacity) {
        size_t new_capacity = queue->capacity * 2;

        CItem *new_items = malloc(sizeof(*new_items) * new_capacity);
        if (new_items == NULL) {
            return false;
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
    queue->items[rear] = data;
    queue->size++;

    return true;
}
bool c_dequeue(CQueue *queue, CItem *data)
{
    if (c_is_empty(queue) || data == NULL) {
        return false;
    }
    *data = queue->items[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return true;
}
bool c_peek(CQueue *queue, CItem *data)
{
    if (c_is_empty(queue) || data == NULL) {
        return false;
    }
    *data = queue->items[queue->front];

    return true;
}
size_t c_size(CQueue *queue)
{
    return queue != NULL ? queue->size : 0;
}
bool c_is_empty(CQueue *queue)
{
    return queue == NULL || queue->size == 0;
}
