#ifndef CIRCULAR_DEQUE_H
#define CIRCULAR_DEQUE_H

#include <stdbool.h>
#include <stddef.h>

typedef int CItem;
typedef struct CircularDeque CDeque;

CDeque *c_create(void);
void c_destroy(CDeque *deque);
void c_push_back(CDeque *deque, int value);
void c_push_front(CDeque *deque, int value);
CItem c_pop_back(CDeque *deque);
CItem c_pop_front(CDeque *deque);
CItem c_front(CDeque *deque);
CItem c_back(CDeque *deque);
bool c_is_empty(CDeque *deque);
size_t c_size(CDeque *deque);

#endif