#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 16

typedef struct {
    size_t key;
    int value;
    bool occupied;
} DAHItem;

bool dah_insert(DAHItem table[], size_t key, int value)
{
    if (key >= SIZE) {
        return false;
    }
    table[key].value = value;
    table[key].occupied = true;

    return true;
}
bool dah_search(DAHItem table[], size_t key, int *value)
{
    if (key >= SIZE || table[key].occupied == false) {
        return false;
    }
    *value = table[key].value;
    return true;
}
bool dah_delete(DAHItem table[], size_t key)
{
    if (key >= SIZE) {
        return false;
    }
    table[key].occupied = 0;

    return true;
}
int main(void)
{
    DAHItem table[SIZE] = {0};
    int value;

    dah_insert(table, 3, 300);
    dah_insert(table, 7, 700);

    if (dah_search(table, 3, &value)) {
        printf("value = %d\n", value);
    } else {
        printf("data is empty.\n");
    }
    dah_delete(table, 3);

    if (dah_search(table, 3, &value)) {
        printf("value = %d\n", value);
    } else {
        printf("data is empty.\n");
    }
    dah_delete(table, 7);

    return 0;
}