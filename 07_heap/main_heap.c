#include "binary_heap.h"
#include <stdio.h>
#include <stdlib.h>

void b_test(void)
{
    BPriorityQueue* pq = b_create();
    if (pq == NULL) {
        return;
    }
    int priorities[] = { 30, 10, 50, 20, 40 };
    size_t count = sizeof(priorities) / sizeof(priorities[0]);
    BItem data;

    for (size_t i = 0; i < count; i++) {
        data.priority = priorities[i];
        b_push(pq, data);
    }
    printf("deleting:\n");

    while (b_size(pq) > 0) {
        printf("%d\n", b_pop(pq));
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
