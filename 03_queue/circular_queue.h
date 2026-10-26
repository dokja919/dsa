#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef int CItem;
typedef struct CircularQueue CQueue;

CQueue *c_create(void);
void c_destroy(CQueue *queue);
bool c_enqueue(CQueue *queue, int value);
bool c_dequeue(CQueue *queue, int *value);
bool c_peek(CQueue *queue, int *value);
bool c_is_empty(CQueue *queue);
size_t c_size(CQueue *queue);

#endif