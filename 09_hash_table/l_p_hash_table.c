#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    LP_INITIAL_CAPACITY = 8 // 16
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
    if (table == NULL) {
        return;
    }
    free(table->items);
    free(table);
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
bool lp_insert(LPSet *table, LPItem data)
{
    if (table == NULL) {
        return false;
    }
    size_t start = lp_hash(table, data.key);
    size_t first_deleted = table->capacity;

    for (size_t i = 0; i < table->capacity; i++) {
        size_t index = (start + i) % table->capacity;
        LPItem *item = &table->items[index];

        if (item->state == LP_OCCUPIED) {
            if (item->key == data.key) {
                return false;
            }
        } else if (item->state == LP_DELETED) {
            if (first_deleted == table->capacity) {
                first_deleted = index;
            }
        } else {
            size_t insert_index = (first_deleted != table->capacity)
                                      ? first_deleted
                                      : index;
            table->items[insert_index].key = data.key;
            table->items[insert_index].state = LP_OCCUPIED;
            table->size++;
            return true;
        }
    }
    if (first_deleted != table->capacity) {
        table->items[first_deleted].key = data.key;
        table->items[first_deleted].state = LP_OCCUPIED;
        table->size++;
        return true;
    }
    return false;
}
bool lp_search(LPSet *table, int key, size_t *index, LPItem *data)
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
            if (index != NULL) {
                *index = target_index;
            }
            if (data != NULL) {
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
    if (lp_search(table, key, &index, &target) == false) {
        return false;
    }
    table->items[index].state = LP_DELETED;
    *data = target;
    table->size--;

    return true;
}
// void lp_print(LPSet *table)
//{
//     for (size_t i = 0; i < table->capacity; i++) {
//         LPItem *current = &table->items[i];
//         printf("[%d] ", i);
//
//         if (current->state == LP_EMPTY) {
//             printf("LP_EMPTY\n");
//         } else if (current->state == LP_DELETED) {
//             printf("LP_DELETED\n");
//         } else {
//             printf("key: %d\n", current->key);
//         }
//     }
// }
//  int main(void)
//{
//      LPSet *table = lp_create();
//
//      lp_insert(table, (LPItem){ 12, LP_EMPTY });
//      lp_insert(table, (LPItem){ 22, LP_EMPTY });
//      lp_insert(table, (LPItem){ 32, LP_EMPTY });
//
//      printf("=== Hash Table ===\n");
//      lp_print(table);
//
//      LPItem data;
//
//      printf("\n=== Search ===\n");
//
//      if (lp_search(table, 22, &data)) {
//          printf("Found: key = 22\n", data.key);
//      } else {
//          printf("Not found\n");
//      }
//
//      printf("\n=== Delete ===\n");
//      lp_delete(table, 22, &data);
//      lp_print(table);
//
//      return 0;
//  }

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
