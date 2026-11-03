#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    LP_INITIAL_CAPACITY = 8
};

typedef enum {
    LP_EMPTY,
    LP_OCCUPIED,
    LP_DELETED
} LPState;

typedef struct {
    int key;
    LPState state;
} LPItem;

typedef struct {
    LPItem *items;
    size_t capacity;
    size_t size;
} LPSet;

LPSet *lp_create(void)
{
    LPSet *table = malloc(sizeof(*table));
    if (table == NULL) {
        return NULL;
    }
    table->capacity = LP_INITIAL_CAPACITY;
    table->size = 0;
    table->items = calloc(table->capacity, sizeof(*table->items));
    if (table->items == NULL) {
        free(table);
        return NULL;
    }
    return table;
}
void lp_destroy(LPSet *table)
{
    if (table != NULL) {
        free(table->items);
        free(table);
    }
}
size_t lp_hash(LPSet *table, int key)
{
    int capacity = (int)table->capacity;
    int remainder = key % capacity;

    if (remainder < 0) {
        remainder += capacity;
    }
    return (size_t)remainder;
}
bool insert(LPSet *table, LPItem data)
{
    if (table == NULL) {
        return false;
    }
    size_t start = lp_hash(table, data.key);
    size_t first_deleted = table->capacity;

    for (size_t i = 0; i < table->capacity; i++) {
        size_t index = (start + i) % table->capacity;
        LPItem *item = &table->items[index];

        if (item->state == LP_OCCUPIED && item->key == data.key) {
            return false;
        } else if (item->state == LP_EMPTY) {
            if (first_deleted != table->capacity) {
                index = first_deleted;
            }
            table->items[index].key = data.key;
            table->items[index].state = LP_OCCUPIED;
            table->size++;
            return false;
        } else if (item->state == LP_DELETED && first_deleted == table->capacity) {
            first_deleted = index;
        }
    }
    if (first_deleted != table->capacity) {
        table->items[first_deleted] = data;
        table->items[first_deleted].state = LP_OCCUPIED;
        table->size++;
        return true;
    }
    return false;
}
bool lp_search(LPSet *table, int key, size_t index, LPItem *data)
{
    if (table == NULL) {
        return false;
    }
    size_t start = lp_hash(table, key);

    for (size_t i = 0; i < table->capacity; i++) {
        size_t target_index = (start + i) % table->capacity;
        LPItem *target = &table->items[target_index];

        if (target->state == LP_EMPTY) {
            return false;
        }
        if (target->state == LP_OCCUPIED && target->key == key) {
            if (data != NULL) {
                index = target_index;
                *data = *target;
            }
            return true;
        }
    }
    return false;
}
bool lp_delete(LPSet *table, int key, LPItem *data)
{
    if (table == NULL) {
        return false;
    }
    size_t index;
    LPItem target;
    if (lp_search(table, key, index, &target) == false) {
        return false;
    }
    table->items[index].state = LP_DELETED;
    *data = target;
    table->size--;

    return true;
}
// int main(void)
//{
//     LPItem data;
//     LPSet *table = lp_create();
//     if (table == NULL) {
//         return 1;
//     }
//     lp_insert(table, 12);
//     lp_insert(table, 20);
//     lp_insert(table, 28);
//     lp_insert(table, 35);
//
//     printf("Key 28 found at %d\n", lp_search(table, 28));
//
//     if (lp_delete(table, 20)) {
//         printf("Key 20 deleted.\n");
//     }
//     printf("Key 28 found at %d\n", lp_search(table, 28, &data));
//     printf("Key 20 found at %d\n", lp_search(table, 20, &data));
//
//     lp_destroy(table);
//     return 0;
// }
