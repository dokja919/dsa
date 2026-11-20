#include "d_h_hash_table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    DH_INITIAL_CAPACITY = 11
};

typedef enum {
    SLOT_EMPTY,
    SLOT_OCCUPIED,
    SLOT_DELETED
} DHState;

typedef struct {
    DHItem data;
    DHState state;
} DHSlot;

struct DoubleHashingHashTable {
    DHSlot* slots;
    size_t capacity;
    size_t size;
    size_t used;
};

DHSet* dh_create(void)
{
    DHSet* table = calloc(1, sizeof(*table));
    if (table == NULL) {
        return NULL;
    }
    table->capacity = DH_INITIAL_CAPACITY;
    table->slots = calloc(table->capacity, sizeof(*table->slots));
    if (table->slots == NULL) {
        free(table);
        return NULL;
    }
    return table;
}
void dh_destroy(DHSet* table)
{
    if (table == NULL) {
        return;
    }
    free(table->slots);
    free(table);
}
static size_t normalize_key(int key, size_t capacity)
{
    return (size_t)key % capacity;
}
static size_t hash1(int key, size_t capacity)
{
    return normalize_key(key, capacity);
}
static size_t hash2(int key, size_t capacity)
{
    return 1 + normalize_key(key, capacity - 1);
}
bool dh_search(DHSet* table, int key, size_t* index_out, DHItem* data_out)
{
    if (table == NULL) {
        return false;
    }
    size_t start = hash1(key, table->capacity);
    size_t step = hash2(key, table->capacity);

    for (size_t i = 0; i < table->capacity; i++) {
        size_t index = (start + i * step) % table->capacity;
        DHSlot* target = &table->slots[index];

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
    }
    return false;
}
static bool is_prime(size_t number)
{
    if (number < 2) {
        return false;
    }
    if (number % 2 == 0) {
        return number == 2;
    }
    for (size_t divisor = 3; divisor * divisor <= number; divisor += 2) {
        if (number % divisor == 0) {
            return false;
        }
    }
    return true;
}
static size_t next_prime(size_t value)
{
    if (value <= 2) {
        return 2;
    }
    if (value % 2 == 0) {
        ++value;
    }
    while (!is_prime(value)) {
        value += 2;
    }
    return value;
}
static bool ensure_capacity(DHSet* table)
{
    if (table == NULL) {
        return false;
    }
    size_t threshold = (table->capacity / 10) * 7 + ((table->capacity % 10) * 7) / 10;
    if (table->used < threshold) {
        return true;
    }
    size_t new_capacity = table->capacity;

    if (table->size >= threshold) {
        new_capacity = next_prime(table->capacity * 2);
    }
    DHSlot* new_slots = calloc(new_capacity, sizeof(*new_slots));
    if (new_slots == NULL) {
        return false;
    }
    for (size_t index = 0; index < table->capacity; index++) {

        DHSlot slot = table->slots[index];
        if (slot.state != SLOT_OCCUPIED) {
            continue;
        }
        size_t start = hash1(slot.data.key, new_capacity);
        size_t step = hash2(slot.data.key, new_capacity);

        for (size_t i = 0; i < new_capacity; ++i) {
            size_t new_index = (start + i * step) % new_capacity;

            if (new_slots[new_index].state != SLOT_OCCUPIED) {
                new_slots[new_index] = slot;
                break;
            }
        }
    }
    free(table->slots);
    table->slots = new_slots;
    table->capacity = new_capacity;
    table->used = table->size;

    return true;
}
bool dh_insert(DHSet* table, DHItem data)
{
    if (table == NULL) {
        return false;
    }
    size_t index;
    if (dh_search(table, data.key, &index, NULL)) {
        table->slots[index].data = data;
        return true;
    }
    if (!ensure_capacity(table)) {
        return false;
    }
    size_t start = hash1(data.key, table->capacity);
    size_t step = hash2(data.key, table->capacity);

    for (size_t i = 0; i < table->capacity; i++) {
        index = (start + i * step) % table->capacity;
        DHSlot* slot = &table->slots[index];

        if (slot->state != SLOT_OCCUPIED) {
            slot->data = data;
            table->size++;
            if (slot->state == SLOT_EMPTY) {
                table->used++;
            }
            slot->state = SLOT_OCCUPIED;

            return true;
        }
    }
    return false;
}
bool dh_delete_at(DHSet* table, size_t index, DHItem* data_out)
{
    if (table == NULL || index >= table->capacity) {
        return false;
    }
    DHSlot* target = &table->slots[index];
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
bool dh_delete(DHSet* table, int key, DHItem* data_out)
{
    if (table == NULL) {
        return false;
    }
    size_t index;
    if (dh_search(table, key, &index, NULL) == false) {
        return false;
    }
    return dh_delete_at(table, index, data_out);
}
