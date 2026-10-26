#include "circular_deque.h"
#include "linked_deque.h"
#include <stdio.h>

void c_test(void)
{
    int value;
    CDeque *deque = c_create();
    if (deque == NULL) {
        return;
    }
    for (int i = 0; i < 8; i++) {
        c_push_front(deque, i);
    }
    if (c_front(deque, &value)) {
        printf("size: %zu, Front: %d\n", c_size(deque), value);
    }
    for (int i = 8; i < 16; i++) {
        c_push_back(deque, i);
    }
    if (c_back(deque, &value)) {
        printf("size: %zu, back: %d\n", c_size(deque), value);
    }
    for (size_t i = 0; i < 8; i++) {
        if (c_pop_front(deque, &value)) {
            printf("popped front: %d\n", value);
        }
    }
    if (c_back(deque, &value)) {
        printf("size: %zu, back: %d\n", c_size(deque), value);
    }
    for (size_t i = 0; i < 8; i++) {
        if (c_pop_back(deque, &value)) {
            printf("popped back: %d\n", value);
        }
    }
    c_destroy(deque);
}
void l_test(void)
{
    LDeque *deque = l_create();

    for (int i = 0; i < 8; i++) {
        l_push_front(deque, i);
    }
    printf("size: %zu, Front: %d\n", l_size(deque), l_front(deque));

    for (int i = 8; i < 16; i++) {
        l_push_back(deque, i);
    }
    printf("size: %zu, back: %d\n", l_size(deque), l_back(deque));
    for (size_t i = 0; i < 8; i++) {
        printf("popped front: %d\n", l_pop_front(deque));
    }
    printf("size: %zu, back: %d\n", l_size(deque), l_back(deque));
    for (size_t i = 0; i < 8; i++) {
        printf("popped back: %d\n", l_pop_back(deque));
    }
    l_destroy(deque);
}
int main(void)
{
    int deque_number = 0;

    switch (deque_number) {
    case 0:
        c_test();
        break;

    case 1:
        l_test();
        break;
    }
    return 0;
}