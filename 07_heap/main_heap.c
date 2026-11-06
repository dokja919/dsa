#include "binary_heap.h"
#include <stdio.h>
#include <stdlib.h>

void b_test(void)
{
    BPriorityQueue* pq = b_create();
    if (pq == NULL) {
        return;
    }
    int priorities[] = { 30, 10, 50, 20, 40, 60, 15, 70, 5, 80, 35, 90 };
    size_t count = sizeof(priorities) / sizeof(priorities[0]);
    BItem data;

    for (size_t i = 0; i < count; i++) {
        data.priority = priorities[i];
        b_push(pq, data);
    }
    printf("deleting:\n");

    while (b_size(pq) > 0) {
        if (b_pop(pq, &data)) {
            printf("%d\n", data.priority);
        }
    }

    b_destroy(pq);
}
int main(void)
{
    int pq_number = 0;

    switch (pq_number) {
    case 0:
        b_test();
        break;
    }
    return 0;
}
