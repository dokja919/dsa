#include "linked_queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    LItem data;
    struct LNode* next;
} l_node;

struct LinkedQueue {
    l_node* rear;
    l_node* front;
};

LQueue* l_create(void)
{
    LQueue* queue = malloc(sizeof(*queue));
    if (queue == NULL) {
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}
void l_destroy(LQueue* queue)
{
    if (queue == NULL) {
        return;
    }
    while (queue->front) {
        l_dequeue(queue);
    }
    free(queue);
}
static l_node* node_create(int value)
{
    l_node* new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}
void l_enqueue(LQueue* queue, int value)
{
    if (queue == NULL) {
        return;
    }
    l_node* new_rear = node_create(value);
    if (new_rear == NULL) {
        return;
    }
    if (queue->front == NULL) {
        queue->front = new_rear;
    } else {
        queue->rear->next = new_rear;
    }
    queue->rear = new_rear;
}
LItem l_dequeue(LQueue* queue)
{
    if (l_is_empty(queue)) {
        return 0;
    }
    l_node* target = queue->front;
    queue->front = target->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    LItem data = target->data;
    free(target);
    return data;
}
LItem l_peek(LQueue* queue)
{
    if (l_is_empty(queue)) {
        return 0;
    }
    return queue->front->data;
}
size_t l_size(LQueue* queue)
{
    if (queue == NULL) {
        return 0;
    }
    size_t size = 0;
    l_node* current = queue->front;

    while (current) {
        size++;
        current = current->next;
    }

    return size;
}
bool l_is_empty(LQueue* queue)
{
    return queue == NULL || queue->front == NULL;
}