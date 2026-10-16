#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef int CItem;
typedef struct CircularQueue CQueue;

CQueue *c_create(void);
void c_destroy(CQueue *queue);
void c_enqueue(CQueue *queue, int value);
CItem c_dequeue(CQueue *queue);
CItem c_peek(CQueue *queue);
bool c_is_empty(CQueue *queue);
size_t c_size(CQueue *queue);

#endif