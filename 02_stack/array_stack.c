#include "array_stack.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 8 // 16

struct ArrayStack {
    AItem *items;
    size_t capacity;
    size_t size;
};

AStack *a_create(void)
{
    AStack *stack = malloc(sizeof(*stack));
    if (stack == NULL) {
        return NULL;
    }
    stack->capacity = INITIAL_CAPACITY;
    stack->items = malloc(sizeof(*stack->items) * stack->capacity);
    if (stack->items == NULL) {
        free(stack);
        return NULL;
    }
    stack->size = 0;

    return stack;
}
void a_destroy(AStack *stack)
{
    if (stack == NULL) {
        return;
    }
    free(stack->items);
    free(stack);
}
bool a_push(AStack *stack, int value)
{
    if (stack == NULL) {
        return false;
    }
    if (stack->size == stack->capacity) {
        size_t new_capacity = stack->capacity * 2;

        AItem *new_items = realloc(stack->items, sizeof(*new_items) * new_capacity);
        if (new_items == NULL) {
            return false;
        }
        stack->items = new_items;
        stack->capacity = new_capacity;
    }
    stack->items[stack->size] = value;
    stack->size++;

    return true;
}
bool a_pop(AStack *stack, int *value)
{
    if (a_is_empty(stack) || value == NULL) {
        return false;
    }
    stack->size--;
    *value = stack->items[stack->size];

    return true;
}
bool a_peek(AStack *stack, int *value)
{
    if (a_is_empty(stack) || value == NULL) {
        return false;
    }
    *value = stack->items[stack->size - 1];

    return true;
}
size_t a_size(AStack *stack)
{
    return stack != NULL ? stack->size : 0;
}
bool a_is_empty(AStack *stack)
{
    return stack == NULL || stack->size == 0;
}