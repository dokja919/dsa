#include "q_p_hash_table.h"
#include <stdbool.h>
#include <stdlib.h>

enum {
    QP_INITIAL_CAPACITY = 11
};

typedef enum {
    SLOT_EMPTY,
    SLOT_OCCUPIED,
    SLOT_DELETED
} QPState;

typedef struct {
    QPItem data;
    QPState state;
} QPSlot;

struct QuadraticProbingHashTable {
    QPSlot* slots;
    size_t capacity;
    size_t size;
};

QPSet* qp_create(void)
{
    QPSet* table = calloc(1, sizeof(*table));
    if (table == NULL) {
        return NULL;
    }
    table->capacity = QP_INITIAL_CAPACITY;
    table->slots = calloc(table->capacity, sizeof(*table->slots));
    if (table->slots == NULL) {
        free(table);
        return NULL;
    }
    return table;
}
void qp_destroy(QPSet* table)
{
    if (table == NULL) {
        return;
    }
    free(table->slots);
    free(table);
}
static size_t qp_hash(size_t capacity, int key)
{
    return (size_t)key % capacity;
}
static bool is_prime(size_t value)
{
    if (value < 2) {
        return false;
    }
    if (value % 2 == 0) {
        return value == 2;
    }
    for (size_t divisor = 3; divisor * divisor <= value; divisor += 2) {
        if (value % divisor == 0) {
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
static bool ensure_capacity(QPSet* table)
{
    if (table == NULL) {
        return false;
    }
    size_t threshold = table->capacity / 2;
    if (table->size < threshold) {
        return true;
    }
    size_t new_capacity = next_prime(table->capacity * 2);
    if (new_capacity == 0) {
        return false;
    }
    QPSlot* new_slots = calloc(new_capacity, sizeof(*new_slots));
    if (new_slots == NULL) {
        return false;
    }
    size_t n = new_capacity / 2 + 1;

    for (size_t index = 0; index < table->capacity; index++) {

        if (table->slots[index].state != SLOT_OCCUPIED) {
            continue;
        }
        size_t hash = qp_hash(new_capacity, table->slots[index].data.key);
        bool inserted = false;

        for (size_t i = 0; i < n; ++i) {
            size_t new_index = (hash + i * i) % new_capacity;

            if (new_slots[new_index].state != SLOT_OCCUPIED) {
                new_slots[new_index] = table->slots[index];
                inserted = true;
                break;
            }
        }
        if (!inserted) {
            free(new_slots);
            return false;
        }
    }
    free(table->slots);
    table->slots = new_slots;
    table->capacity = new_capacity;

    return true;
}
bool qp_insert(QPSet* table, QPItem data)
{
    if (table == NULL) {
        return false;
    }
    size_t index;
    if (qp_search(table, data.key, &index, NULL)) {
        table->slots[index].data = data;
        return true;
    }
    if (!ensure_capacity(table)) {
        return false;
    }
    size_t hash = qp_hash(table->capacity, data.key);
    size_t n = table->capacity / 2 + 1;

    for (size_t i = 0; i < n; ++i) {
        index = (hash + i * i) % table->capacity;
        QPSlot* slot = &table->slots[index];

        if (slot->state != SLOT_OCCUPIED) {
            slot->data = data;
            slot->state = SLOT_OCCUPIED;
            table->size++;

            return true;
        }
    }
    return false;
}
bool qp_search(QPSet* table, int key, size_t* index_out, QPItem* data_out)
{
    if (table == NULL) {
        return false;
    }
    size_t hash = qp_hash(table->capacity, key);
    size_t n = table->capacity / 2 + 1;

    for (size_t i = 0; i < n; ++i) {
        size_t index = (hash + i * i) % table->capacity;
        QPSlot* target = &table->slots[index];

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
bool qp_delete_at(QPSet* table, size_t index, QPItem* data_out)
{
    if (table == NULL || index >= table->capacity) {
        return false;
    }
    QPSlot* target = &table->slots[index];
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
bool qp_delete(QPSet* table, int key, QPItem* data_out)
{
    if (table == NULL) {
        return false;
    }
    size_t index;
    if (!qp_search(table, key, &index, NULL)) {
        return false;
    }
    return qp_delete_at(table, index, data_out);
}
