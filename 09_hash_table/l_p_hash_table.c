#include "l_p_hash_table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    INITIAL_CAPACITY = 8 // 16
};

enum State {
    SLOT_EMPTY,
    SLOT_OCCUPIED,
    SLOT_DELETED
};

struct LinearProbingHashTable {
    LPSlot* items;
    size_t capacity;
    size_t size;
};

LPSet* lp_create(void)
{
    LPSet* table = malloc(sizeof(*table));
    if (table == NULL) {
        return NULL;
    }
    table->capacity = INITIAL_CAPACITY;
    table->size = 0;
    table->items = calloc(table->capacity, sizeof(*table->items));
    if (table->items == NULL) {
        free(table);
        return NULL;
    }
    return table;
}
void lp_destroy(LPSet* table)
{
    if (table == NULL) {
        return;
    }
    free(table->items);
    free(table);
}
size_t lp_hash(LPSet* table, int key)
{
    return (size_t)key % table->capacity;
}
bool lp_insert(LPSet* table, int key)
{
    if (table == NULL) {
        return false;
    }
    size_t start = lp_hash(table, key);
    size_t first_deleted = table->capacity;

    for (size_t i = 0; i < table->capacity; i++) {
        size_t index = (start + i) % table->capacity;
        LPSlot* item = &table->items[index];

        if (item->state == SLOT_OCCUPIED) {
            if (item->key == key) {
                return false;
            }
        } else if (item->state == SLOT_DELETED) {
            if (first_deleted == table->capacity) {
                first_deleted = index;
            }
        } else {
            size_t insert_index = (first_deleted != table->capacity)
                                      ? first_deleted
                                      : index;
            table->items[insert_index].key = key;
            table->items[insert_index].state = SLOT_OCCUPIED;
            table->size++;
            return true;
        }
    }
    if (first_deleted != table->capacity) {
        table->items[first_deleted].key = key;
        table->items[first_deleted].state = SLOT_OCCUPIED;
        table->size++;
        return true;
    }
    return false;
}
bool lp_search(LPSet* table, int key, size_t* index, LPSlot* data)
{
    if (table == NULL) {
        return false;
    }
    size_t start = lp_hash(table, key);

    for (size_t i = 0; i < table->capacity; i++) {
        size_t target_index = (start + i) % table->capacity;
        LPSlot* target = &table->items[target_index];

        if (target->state == SLOT_EMPTY) {
            return false;
        }
        if (target->state == SLOT_OCCUPIED && target->key == key) {
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
bool lp_delete(LPSet* table, int key, LPSlot* data)
{
    if (table == NULL) {
        return false;
    }
    size_t index;
    LPSlot target;
    if (lp_search(table, key, &index, &target) == false) {
        return false;
    }
    table->items[index].state = SLOT_DELETED;
    *data = target;
    table->size--;

    return true;
}