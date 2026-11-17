#define _CRT_SECURE_NO_WARNINGS
#include "array_stack.h"
#include "linked_stack.h"
#include <stdio.h>

void a_test(void)
{
    AItem data;
    AStack* stack = a_create();
    if (stack == NULL) {
        return;
    }
    for (int i = 1; i <= 10; i++) {
        a_push(stack, i * 10);
    }
    if (a_peek(stack, &data)) {
        printf("Size : %zu, Top: %d\n", a_size(stack), data);
    }
    while (a_is_empty(stack) == false) {
        if (a_pop(stack, &data)) {
            printf("Popped: %d\n", data);
        }
    }
    printf("Size: %zu\n", a_size(stack));

    a_destroy(stack);
}
void l_test(void)
{
    LStack* stack = l_create();

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