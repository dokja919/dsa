#include "l_p_hash_table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    INITIAL_CAPACITY = 8 // 16
};

typedef enum {
    SLOT_EMPTY,
    SLOT_OCCUPIED,
    SLOT_DELETED
} LPState;

typedef struct {
    LPItem data;
    LPState state;
} LPSlot;

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
        size_t index = lp_hash(new_capacity, table->slots[i].data.key);

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
bool lp_insert(LPSet* table, LPItem data)
{
    if (table == NULL) {
        return false;
    }
    size_t index;
    if (lp_search(table, data.key, &index, NULL)) {
        table->slots[index].data = data;
        return true;
    }
    if (ensure_capacity(table) == false) {
        return false;
    }
    index = lp_hash(table->capacity, data.key);

    for (size_t i = 0; i < table->capacity; i++) {
        LPSlot* slot = &table->slots[index];

        if (slot->state != SLOT_OCCUPIED) {
            slot->data = data;
            slot->state = SLOT_OCCUPIED;
            table->size++;

            return true;
        }
        index = (index + 1 == table->capacity) ? 0 : index + 1;
    }
    return false;
}
bool lp_search(LPSet* table, int key, size_t* index_out, LPItem* data_out)
{
    if (table == NULL) {
        return false;
    }
    size_t index = lp_hash(table->capacity, key);

    for (size_t i = 0; i < table->capacity; i++) {
        LPSlot* target = &table->slots[index];

        if (target->state == SLOT_EMPTY) {
            return false;
        }
        if (target->state == SLOT_OCCUPIED && target->data.key == key) {
            if (index_out != NULL) {
                *index_out = index;
            }
            if (data_out != NULL) {
                *data_out = target->data;
            }
            return true;
        }
        index = (index + 1 == table->capacity) ? 0 : index + 1;
    }
    return false;
}
bool lp_delete_at(LPSet* table, size_t index, LPItem* data_out)
{
    if (table == NULL || index >= table->capacity) {
        return false;
    }
    LPSlot* target = &table->slots[index];
    if (target->state != SLOT_OCCUPIED) {
        return false;
    }
    if (data_out != NULL) {
        *data_out = target->data;
    }
    target->state = SLOT_DELETED;
    table->size--;

    return true;
}
bool lp_delete(LPSet* table, int key, LPItem* data_out)
{
    if (table == NULL) {
        return false;
    }
    size_t index;
    if (lp_search(table, key, &index, NULL) == false) {
        return false;
    }
    return lp_delete_at(table, index, data_out);
}