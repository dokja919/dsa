#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef int AItem;
typedef struct ArrayStack AStack;

AStack *a_create(void);
void a_destroy(AStack *stack);
bool a_push(AStack *stack, AItem data);
bool a_pop(AStack *stack, AItem *data);
bool a_peek(AStack *stack, AItem *data);
bool a_is_empty(AStack *stack);
size_t a_size(AStack *stack);

#endif
