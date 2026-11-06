#include "s_c_hash_table.h"
#include <stdlib.h>

enum { SC_CAPACITY = 16 };

typedef struct SCNode {
    SCItem data;
    struct SCNode* prev;
    struct SCNode* next;
} SCNode;

struct SeparateChainingHashTable {
    SCNode* buckets[SC_CAPACITY];
};
SCSet* sc_create(void)
{
    return calloc(1, sizeof(SCSet));
}
void sc_destroy(SCSet* table)
{
    if (table == NULL) {
        return;
    }
    for (size_t i = 0; i < SC_CAPACITY; i++) {
        SCNode* current = table->buckets[i];

        while (current != NULL) {
            SCNode* next = current->next;
            free(current);
            current = next;
        }
    }
    free(table);
}
size_t sc_hash(int key)
{
    int remainder = key % SC_CAPACITY;

    if (remainder < 0) {
        remainder += SC_CAPACITY;
    }
    return (size_t)remainder;
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
bool sc_insert(SCSet* table, SCItem data)
{
    if (table == NULL) {
        return false;
    }
    size_t index = sc_hash(data.key);

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
    new_node->next = table->buckets[index];
    if (table->buckets[index] != NULL) {
        table->buckets[index]->prev = new_node;
    }
    table->buckets[index] = new_node;

    return true;
}
bool sc_search(SCSet* table, int key, SCIter* out_iter)
{
    if (out_iter != NULL) {
        *out_iter = NULL;
    }
    if (table == NULL) {
        return false;
    }
    size_t index = sc_hash(key);

    for (SCNode* current = table->buckets[index]; current != NULL; current = current->next) {

        if (current->data.key == key) {

            if (out_iter != NULL) {
                *out_iter = current;
            }
            return true;
        }
    }
    return false;
}
bool sc_get(SCIter iter, SCItem* out_data)
{
    if (iter == NULL || out_data == NULL) {
        return false;
    }
    *out_data = iter->data;
    return true;
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
bool sc_delete(SCSet* table, int key, SCItem* out_data)
{
    if (table == NULL) {
        return false;
    }
    size_t index = sc_hash(key);
    SCNode* target = table->buckets[index];

    while (target != NULL) {

        if (target->data.key == key) {

            if (out_data != NULL) {
                *out_data = target->data;
            }
            node_unlink(table, index, target);
            free(target);
            return true;
        }
        target = target->next;
    }
    return false;
}
bool sc_delete_iter(SCSet* table, SCIter target, SCItem* out_data)
{
    if (table == NULL || target == NULL) {
        return false;
    }
    size_t index = sc_hash(target->data.key);

    if (out_data != NULL) {
        *out_data = target->data;
    }
    node_unlink(table, index, target);
    free(target);

    return true;
}