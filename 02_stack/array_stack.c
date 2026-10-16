#include "array_stack.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 8

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
void a_push(AStack *stack, int value)
{
    if (stack == NULL) {
        return;
    }
    if (stack->size == stack->capacity) {
        size_t new_capacity = stack->capacity * 2;

        AItem *new_items = realloc(stack->items, sizeof(*new_items) * new_capacity);
        if (new_items == NULL) {
            return;
        }
        stack->items = new_items;
        stack->capacity = new_capacity;
    }
    stack->items[stack->size] = value;
    stack->size++;
}
AItem a_pop(AStack *stack)
{
    if (a_is_empty(stack)) {
        return 0;
    }
    stack->size--;

    return stack->items[stack->size];
}
AItem a_peek(AStack *stack)
{
    if (a_is_empty(stack)) {
        return 0;
    }

    return stack->items[stack->size - 1];
}
size_t a_size(AStack *stack)
{
    return stack ? stack->size : 0;
}
bool a_is_empty(AStack *stack)
{
    return stack == NULL || stack->size == 0;
}