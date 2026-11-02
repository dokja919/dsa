#include <stdio.h>

enum {
    LP_INITIAL_CAPACITY = 8 // 16
};

typedef enum {
    EMPTY,
    OCCUPIED,
    DELETED
} LPState;

typedef struct {
    int key;
    LPState state;
} LPItem;

typedef struct {
    LPItem items[LP_INITIAL_CAPACITY];
} LPSet;

size_t lp_hash(int key)
{
    int remainder = key % LP_INITIAL_CAPACITY;

    if (remainder < 0) {
        remainder += LP_INITIAL_CAPACITY;
    }
    return (size_t)remainder;
}
void insert(int *table, int key)
{
    size_t index = lp_hash(key);
    if (table[index] != 0) {
        size_t i = 0;
        while (table[(index + i) % LP_INITIAL_CAPACITY] != 0) {
            i++;
        }
        index = (index + i) % LP_INITIAL_CAPACITY;
    }
    table[index] = key;
}
int search(int *table, int key)
{
    int index = lp_hash(key);
    int i = 0;
    while (table[(index + i) % LP_INITIAL_CAPACITY] != key) {
        i++;
    }
    return (index + i) % LP_INITIAL_CAPACITY;
}
int main()
{
    int table[10] = { 0 };
    insert(table, 12);
    insert(table, 25);
    insert(table, 35);
    insert(table, 26);
    printf("\nKey found at %d\n", search(table, 35));
    return 0;
}