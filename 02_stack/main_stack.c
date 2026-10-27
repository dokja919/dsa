#define _CRT_SECURE_NO_WARNINGS
#include "array_stack.h"
#include "linked_stack.h"
#include <stdio.h>

void a_test(void)
{
    AItem value;
    AStack *stack = a_create();
    if (stack == NULL) {
        return;
    }
    a_push(stack, 3);
    a_push(stack, 37);
    a_push(stack, 11);
    a_push(stack, 12);
    if (a_peek(stack, &value)) {
        printf("size: %zu, Top: %d\n", a_size(stack), value);
    }

    while (a_is_empty(stack) == false) {
        if (a_pop(stack, &value)) {
            printf("Popped: %d\n", value);
        }
    }
    printf("stack Is Empty.\n");

    a_destroy(stack);
}
void l_test(void)
{
    LStack *stack = l_create();

    l_push(stack, 10);
    l_push(stack, 20);
    l_push(stack, 30);
    l_push(stack, 40);

    printf("size: %zu, Top: %d\n\n", l_size(stack), l_top(stack));

    while (l_is_empty(stack) == false) {
        printf("Popped: %d\n", l_pop(stack));
    }

    printf("stack Is Empty.\n");

    l_destroy(stack);
}

int main(void)
{
    int stack_number = 0;

    switch (stack_number) {
    case 0:
        a_test();
        break;

    case 1:
        l_test();
        break;
    }

    return 0;
}