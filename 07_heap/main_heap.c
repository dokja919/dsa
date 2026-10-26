#include "binary_heap.h"
#include <stdio.h>
#include <stdlib.h>

void b_test(void)
{
    BPriorityQueue *pq = b_create();
    int priorities[] = {30, 10, 50, 20, 40};

    for (size_t i = 0; i < 5; i++) {
        b_insert(pq, priorities[i]);
    }
    printf("deleting:\n");

    while (b_size(pq) > 0) {
        printf("%d\n", b_extract(pq));
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
