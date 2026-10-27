#ifndef CIRCULAR_DEQUE_H
#define CIRCULAR_DEQUE_H

#include <stdbool.h>
#include <stddef.h>

typedef int CItem;
typedef struct CircularDeque CDeque;

CDeque *c_create(void);
void c_destroy(CDeque *deque);
bool c_push_back(CDeque *deque, CItem data);
bool c_push_front(CDeque *deque, CItem data);
bool c_pop_back(CDeque *deque, CItem *data);
bool c_pop_front(CDeque *deque, CItem *data);
bool c_front(CDeque *deque, CItem *data);
bool c_back(CDeque *deque, CItem *data);
bool c_is_empty(CDeque *deque);
size_t c_size(CDeque *deque);

#endif