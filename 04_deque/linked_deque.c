#include "linked_deque.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    LItem data;
    struct LNode* next;
    struct LNode* prev;
} LNode;

struct LinkedDeque {
    LNode* rear;
    LNode* front;
};

LDeque* l_create(void)
{
    LDeque* deque = malloc(sizeof(*deque));
    if (deque == NULL) {
        return NULL;
    }

    deque->front = NULL;
    deque->rear = NULL;

    return deque;
}
void l_destroy(LDeque* deque)
{
    if (deque == NULL) {
        return;
    }
    while (deque->front) {
        l_pop_front(deque);
    }
    free(deque);
}
static LNode* node_create(int value)
{
    LNode* new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}
void l_push_front(LDeque* deque, int value)
{
    if (deque == NULL) {
        return;
    }
    LNode* new_front = node_create(value);
    if (new_front == NULL) {
        return;
    }
    if (deque->rear == NULL) {
        deque->rear = new_front;
    } else {
        new_front->next = deque->front;
        deque->front->prev = new_front;
    }
    deque->front = new_front;
}
void l_push_back(LDeque* deque, int value)
{
    if (deque == NULL) {
        return;
    }
    LNode* new_rear = node_create(value);
    if (new_rear == NULL) {
        return;
    }

    if (deque->front == NULL) {
        deque->front = new_rear;
    } else {
        new_rear->prev = deque->rear;
        deque->rear->next = new_rear;
    }
    deque->rear = new_rear;
}
LItem l_pop_front(LDeque* deque)
{
    if (l_is_empty(deque)) {
        return 0;
    }
    LNode* target = deque->front;
    deque->front = target->next;

    if (deque->front == NULL) {
        deque->rear = NULL;
    } else {
        deque->front->prev = NULL;
    }
    LItem data = target->data;
    free(target);
    return data;
}
LItem l_pop_back(LDeque* deque)
{
    if (l_is_empty(deque)) {
        return 0;
    }
    LNode* target = deque->rear;
    deque->rear = target->prev;

    if (deque->rear == NULL) {
        deque->front = NULL;
    } else {
        deque->rear->next = NULL;
    }
    LItem data = target->data;
    free(target);
    return data;
}
LItem l_front(LDeque* deque)
{
    if (l_is_empty(deque)) {
        return 0;
    }
    return deque->front->data;
}
LItem l_back(LDeque* deque)
{
    if (l_is_empty(deque)) {
        return 0;
    }
    return deque->rear->data;
}
size_t l_size(LDeque* deque)
{
    if (deque == NULL) {
        return 0;
    }
    size_t size = 0;
    LNode* current = deque->front;

    while (current) {
        size++;
        current = current->next;
    }
    return size;
}
bool l_is_empty(LDeque* deque)
{
    return deque == NULL || deque->front == NULL;
}