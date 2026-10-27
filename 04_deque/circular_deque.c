#include "circular_deque.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 8 // 16

struct CircularDeque {
    CItem *items;
    size_t capacity;
    size_t front;
    size_t size;
};

CDeque *c_create(void)
{
    CDeque *deque = malloc(sizeof(*deque));
    if (deque == NULL) {
        return NULL;
    }
    deque->capacity = INITIAL_CAPACITY;
    deque->items = malloc(sizeof(*deque->items) * deque->capacity);
    if (deque->items == NULL) {
        free(deque);
        return NULL;
    }
    deque->front = 0;
    deque->size = 0;

    return deque;
}
void c_destroy(CDeque *deque)
{
    if (deque == NULL) {
        return;
    }
    free(deque->items);
    free(deque);
}
static bool c_ensure_capacity(CDeque *deque)
{
    size_t new_capacity = deque->capacity * 2;

    CItem *new_items = malloc(sizeof(*new_items) * new_capacity);
    if (new_items == NULL) {
        return false;
    }
    for (size_t i = 0; i < deque->capacity; i++) {
        size_t j = (deque->front + i) % deque->capacity;
        new_items[i] = deque->items[j];
    }
    free(deque->items);
    deque->items = new_items;
    deque->capacity = new_capacity;
    deque->front = 0;

    return true;
}
bool c_push_back(CDeque *deque, CItem data)
{
    if (deque == NULL) {
        return false;
    }
    if (deque->size >= deque->capacity) {
        if (c_ensure_capacity(deque) == false) {
            return false;
        }
    }
    size_t back = (deque->front + deque->size) % deque->capacity;
    deque->items[back] = data;
    deque->size++;

    return true;
}
bool c_push_front(CDeque *deque, CItem data)
{
    if (deque == NULL) {
        return false;
    }
    if (c_ensure_capacity(deque) == false) {
        if (deque->size == deque->capacity) {
            return false;
        }
    }
    deque->front = (deque->capacity + deque->front - 1) % deque->capacity;
    deque->items[deque->front] = data;
    deque->size++;

    return true;
}
bool c_pop_back(CDeque *deque, CItem *data)
{
    if (c_is_empty(deque) || data == NULL) {
        return false;
    }
    size_t back = (deque->front + deque->size - 1) % deque->capacity;
    *data = deque->items[back];
    deque->size--;

    return true;
}
bool c_pop_front(CDeque *deque, CItem *data)
{
    if (c_is_empty(deque) || data == NULL) {
        return false;
    }
    *data = deque->items[deque->front];
    deque->front = (deque->front + 1) % deque->capacity;
    deque->size--;

    return true;
}
bool c_front(CDeque *deque, CItem *data)
{
    if (c_is_empty(deque) || data == NULL) {
        return false;
    }
    *data = deque->items[deque->front];

    return true;
}
bool c_back(CDeque *deque, CItem *data)
{
    if (c_is_empty(deque) || data == NULL) {
        return false;
    }
    size_t back = (deque->front + deque->size - 1) % deque->capacity;
    *data = deque->items[back];

    return true;
}
bool c_is_empty(CDeque *deque)
{
    return deque == NULL || deque->size == 0;
}
size_t c_size(CDeque *deque)
{
    return deque != NULL ? deque->size : 0;
}