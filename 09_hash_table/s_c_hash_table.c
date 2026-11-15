#include "s_c_hash_table.h"
#include <stdlib.h>

enum {
    INITIAL_CAPACITY = 16
};

typedef struct SCNode {
    SCItem data;
    struct SCNode* prev;
    struct SCNode* next;
} SCNode;

struct SeparateChainingHashTable {
    SCNode** buckets;
    size_t capacity;
    size_t size;
};
SCSet* sc_create(void)
{
    SCSet* table = calloc(1, sizeof(*table));
    if (table == NULL) {
        return NULL;
    }
    table->buckets = calloc(INITIAL_CAPACITY, sizeof(*table->buckets));
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }
    table->capacity = INITIAL_CAPACITY;

    return table;
}
void sc_destroy(SCSet* table)
{
    if (table == NULL) {
        return;
    }
    for (size_t i = 0; i < table->capacity; i++) {
        SCNode* current = table->buckets[i];

        while (current != NULL) {
            SCNode* next = current->next;
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}
static SCNode* node_create(SCItem data)
{
    SCNode* new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}
static size_t sc_hash(int key, size_t capacity)
{
    return (size_t)key % capacity;
}
static bool ensure_capacity(SCSet* table)
{
    if (table == NULL) {
        return false;
    }
    size_t threshold = table->capacity - table->capacity / 4;
    if (table->size < threshold) {
        return true;
    }
    size_t new_capacity = table->capacity * 2;

    SCNode** new_buckets = calloc(new_capacity, sizeof(*new_buckets));
    if (new_buckets == NULL) {
        return false;
    }
    for (size_t i = 0; i < table->capacity; i++) {
        SCNode* current = table->buckets[i];

        while (current != NULL) {
            SCNode* next = current->next;
            size_t index = sc_hash(current->data.key, new_capacity);

            current->prev = NULL;
            current->next = new_buckets[index];

            if (new_buckets[index] != NULL) {
                new_buckets[index]->prev = current;
            }

            new_buckets[index] = current;
            current = next;
        }
    }
    free(table->buckets);
    table->buckets = new_buckets;
    table->capacity = new_capacity;

    return true;
}
bool sc_insert(SCSet* table, SCItem data)
{
    if (table == NULL) {
        return false;
    }
    size_t index = sc_hash(data.key, table->capacity);

    for (SCNode* current = table->buckets[index]; current != NULL; current = current->next) {
        if (current->data.key == data.key) {
            current->data = data;
            return true;
        }
    }
    SCNode* new_node = node_create(data);
    if (new_node == NULL) {
        return false;
    }
    if (ensure_capacity(table) == false) {
        free(new_node);
        return false;
    }
    index = sc_hash(data.key, table->capacity);

    new_node->next = table->buckets[index];
    if (table->buckets[index] != NULL) {
        table->buckets[index]->prev = new_node;
    }
    table->buckets[index] = new_node;
    table->size++;

    return true;
}
bool sc_search(SCSet* table, int key, SCIter* iter_out, SCItem* data_out)
{
    if (iter_out != NULL) {
        *iter_out = NULL;
    }
    if (table == NULL) {
        return false;
    }
    size_t index = sc_hash(key, table->capacity);

    for (SCNode* current = table->buckets[index]; current != NULL; current = current->next) {

        if (current->data.key == key) {

            if (iter_out != NULL) {
                *iter_out = current;
            }
            if (data_out != NULL) {
                *data_out = current->data;
            }
            return true;
        }
    }
    return false;
}
static void node_unlink(SCSet* table, size_t index, SCNode* node)
{
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        table->buckets[index] = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
}
bool sc_delete(SCSet* table, int key, SCItem* data_out)
{
    if (table == NULL) {
        return false;
    }
    size_t index = sc_hash(key, table->capacity);
    SCNode* target = table->buckets[index];

    while (target != NULL) {

        if (target->data.key == key) {

            if (data_out != NULL) {
                *data_out = target->data;
            }
            node_unlink(table, index, target);
            free(target);
            table->size--;

            return true;
        }
        target = target->next;
    }
    return false;
}
bool sc_delete_iter(SCSet* table, SCIter target, SCItem* data_out)
{
    if (table == NULL || target == NULL) {
        return false;
    }
    size_t index = sc_hash(target->data.key, table->capacity);

    if (data_out != NULL) {
        *data_out = target->data;
    }
    node_unlink(table, index, target);
    free(target);
    table->size--;

    return true;
}