#include "linked_stack.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    LItem data;
    struct LNode* next;
} LNode;

struct LinkedStack {
    LNode* top;
};

LStack* l_create(void)
{
    LStack* stack = malloc(sizeof(*stack));

    if (stack == NULL) {
        return NULL;
    }

    stack->top = NULL;

    return stack;
}
void l_destroy(LStack* stack)
{
    if (stack == NULL) {
        return;
    }

    while (!l_is_empty(stack)) {
        l_pop(stack);
    }

    free(stack);
}
static LNode* node_create(int value)
{
    LNode* new_node = malloc(sizeof(*new_node));

    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}
void l_push(LStack* stack, int value)
{
    if (stack == NULL) {
        return;
    }

    LNode* new_top = node_create(value);

    if (new_top == NULL) {
        return;
    }

    new_top->next = stack->top;
    stack->top = new_top;
}

LItem l_pop(LStack* stack)
{
    if (l_is_empty(stack)) {
        return 0;
    }

    LNode* target = stack->top;
    stack->top = target->next;

    LItem value = target->data;
    free(target);
    return value;
}

LItem l_top(LStack* stack)
{
    if (l_is_empty(stack)) {
        return 0;
    }

    return stack->top->data;
}
size_t l_size(LStack* stack)
{
    if (stack == NULL) {
        return 0;
    }

    size_t size = 0;
    LNode* current = stack->top;

    while (current != NULL) {
        size++;
        current = current->next;
    }

    return size;
}
bool l_is_empty(LStack* stack)
{
    return stack == NULL || stack->top == NULL;
}