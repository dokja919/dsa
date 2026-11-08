#include "l_p_hash_table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    INITIAL_CAPACITY = 8 // 16
};

struct LinearProbingHashTable {
    LPSlot* slots;
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
    table->slots = calloc(table->capacity, sizeof(*table->slots));
    if (table->slots == NULL) {
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
    free(table->slots);
    free(table);
}
static size_t lp_hash(size_t capacity, int key)
{
    return (size_t)key % capacity;
}
static bool ensure_capacity(LPSet* table)
{
    if (table == NULL) {
        return false;
    }
    size_t threshold = (table->capacity / 10) * 7 + ((table->capacity % 10) * 7) / 10;
    if (table->size < threshold) {
        return true;
    }
    size_t new_capacity = table->capacity * 2;

    LPSlot* new_slots = calloc(new_capacity, sizeof(*new_slots));
    if (new_slots == NULL) {
        return false;
    }
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->slots[i].state != SLOT_OCCUPIED) {
            continue;
        }
        size_t index = lp_hash(new_capacity, table->slots[i].key);

        while (new_slots[index].state == SLOT_OCCUPIED) {
            index = (index + 1) % new_capacity;
        }
        new_slots[index] = table->slots[i];
    }
    free(table->slots);
    table->slots = new_slots;
    table->capacity = new_capacity;

    return true;
}
bool lp_insert(LPSet* table, int key)
{
    if (table == NULL) {
        return false;
    }
    if (ensure_capacity(table) == false) {
        return false;
    }
    size_t start = lp_hash(table->capacity, key);
    size_t first_deleted = table->capacity;

    for (size_t i = 0; i < table->capacity; i++) {
        size_t index = (start + i) % table->capacity;
        LPSlot* item = &table->slots[index];

        if (item->state == SLOT_OCCUPIED) {
            if (item->key == key) {
                return true;
            }
        } else if (item->state == SLOT_DELETED) {
            if (first_deleted == table->capacity) {
                first_deleted = index;
            }
        } else {
            size_t insert_index = (first_deleted != table->capacity)
                                      ? first_deleted
                                      : index;
            table->slots[insert_index].key = key;
            table->slots[insert_index].state = SLOT_OCCUPIED;
            table->size++;
            return true;
        }
    }
    if (first_deleted != table->capacity) {
        table->slots[first_deleted].key = key;
        table->slots[first_deleted].state = SLOT_OCCUPIED;
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
    size_t start = lp_hash(table->capacity, key);

    for (size_t i = 0; i < table->capacity; i++) {
        size_t target_index = (start + i) % table->capacity;
        LPSlot* target = &table->slots[target_index];

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
    LPSlot target;
    if (lp_search(table, key, NULL, &target) == false) {
        return false;
    }
    if (data != NULL) {
        *data = target;
    }
    target.state = SLOT_DELETED;

    table->size--;

    return true;
}