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
    printf("Heap size: %zu\n", b_size(pq));

    if (heap_peek(pq, &data)) {
        printf("Top priority: %d\n", data.priority);
    }

    while (b_is_empty(pq) == false) {
        if (b_pop(pq, &data)) {
            printf("Pop: %d\n", data.priority);
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
