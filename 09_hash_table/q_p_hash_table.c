#include "l_p_hash_table.h"
#include <stdbool.h>
#include <stdlib.h>

/*
 * Simple quadratic probing:
 *     index(i) = (hash(key) + i * i) % capacity
 *
 * The table capacity is always prime, and the number of stored items is kept
 * at or below half the capacity. The LP-prefixed API is kept for compatibility
 * with the existing caller code.
 */
enum {
    LP_INITIAL_CAPACITY = 7
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

struct QuadraticProbingHashTable {
    LPSlot* slots;
    size_t capacity;
    size_t size;
};

static bool is_prime(size_t value)
{
    if (value < 2) {
        return false;
    }
    if (value % 2 == 0) {
        return value == 2;
    }
    for (size_t divisor = 3; divisor <= value / divisor; divisor += 2) {
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
        if (value > (size_t)-1 - 2) {
            return 0;
        }
        value += 2;
    }
    return value;
}

LPSet* lp_create(void)
{
    LPSet* table = malloc(sizeof(*table));
    if (table == NULL) {
        return NULL;
    }

    table->capacity = LP_INITIAL_CAPACITY;
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

/* Returns the i-th slot in the quadratic probing sequence. */
static size_t lp_probe_index(size_t capacity, size_t hash, size_t attempt)
{
    size_t offset = (attempt * attempt) % capacity;

    /* Compute (hash + offset) % capacity without overflowing the sum. */
    if (hash >= capacity - offset) {
        return hash - (capacity - offset);
    }
    return hash + offset;
}

/*
 * For a prime capacity p, i*i (mod p) visits (p + 1) / 2 distinct slots.
 * This is the number of distinct positions we need to inspect.
 */
static size_t lp_probe_count(size_t capacity)
{
    return capacity / 2 + 1;
}

static bool ensure_capacity(LPSet* table)
{
    if (table == NULL) {
        return false;
    }

    /* Keep the load factor at or below 0.5. */
    size_t threshold = table->capacity / 2;
    if (table->size < threshold) {
        return true;
    }

    if (table->capacity > (size_t)-1 / 2) {
        return false;
    }
    size_t new_capacity = next_prime(table->capacity * 2);
    if (new_capacity == 0) {
        return false;
    }

    LPSlot* new_slots = calloc(new_capacity, sizeof(*new_slots));
    if (new_slots == NULL) {
        return false;
    }

    size_t probe_count = lp_probe_count(new_capacity);
    for (size_t i = 0; i < table->capacity; ++i) {
        if (table->slots[i].state != SLOT_OCCUPIED) {
            continue;
        }

        size_t hash = lp_hash(new_capacity, table->slots[i].data.key);
        bool placed = false;
        for (size_t attempt = 0; attempt < probe_count; ++attempt) {
            size_t index = lp_probe_index(new_capacity, hash, attempt);
            if (new_slots[index].state != SLOT_OCCUPIED) {
                new_slots[index] = table->slots[i];
                placed = true;
                break;
            }
        }

        if (!placed) {
            free(new_slots);
            return false;
        }
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

    /* Update an existing key instead of inserting a duplicate. */
    size_t index;
    if (lp_search(table, data.key, &index, NULL)) {
        table->slots[index].data = data;
        return true;
    }

    if (!ensure_capacity(table)) {
        return false;
    }

    size_t hash = lp_hash(table->capacity, data.key);
    size_t probe_count = lp_probe_count(table->capacity);

    for (size_t attempt = 0; attempt < probe_count; ++attempt) {
        index = lp_probe_index(table->capacity, hash, attempt);
        LPSlot* slot = &table->slots[index];

        if (slot->state != SLOT_OCCUPIED) {
            slot->data = data;
            slot->state = SLOT_OCCUPIED;
            table->size++;
            return true;
        }
    }

    return false;
}

bool lp_search(LPSet* table, int key, size_t* index_out, LPItem* data_out)
{
    if (table == NULL) {
        return false;
    }

    size_t hash = lp_hash(table->capacity, key);
    size_t probe_count = lp_probe_count(table->capacity);

    for (size_t attempt = 0; attempt < probe_count; ++attempt) {
        size_t index = lp_probe_index(table->capacity, hash, attempt);
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
        /* SLOT_DELETED must not stop the search. */
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
    if (!lp_search(table, key, &index, NULL)) {
        return false;
    }
    return lp_delete_at(table, index, data_out);
}
