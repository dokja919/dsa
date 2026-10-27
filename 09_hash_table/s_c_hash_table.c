#include "s_c_hash_table.h"
#include <stdlib.h>

enum { SC_CAPACITY = 16 };

typedef struct SCNode {
    SCItem data;
    struct SCNode *next;
} SCNode;

struct SCHashTable {
    SCNode **buckets;
};

SCHashTable *sc_create(void)
{
    SCHashTable *table = malloc(sizeof(*table));
    if (table == NULL) {
        return NULL;
    }
    table->buckets = calloc(SC_CAPACITY, sizeof(*table->buckets));
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }
    return table;
}
void sc_destroy(SCHashTable *table)
{
    if (table == NULL) {
        return;
    }
    for (size_t i = 0; i < SC_CAPACITY; i++) {
        SCNode *current = table->buckets[i];

        while (current != NULL) {
            SCNode *next = current->next;
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}
size_t sc_hash(int key)
{
    return (size_t)(((key % SC_CAPACITY) + SC_CAPACITY) % SC_CAPACITY);
}
bool sc_insert(SCHashTable *table, SCItem data)
{
    if (table == NULL) {
        return false;
    }
    size_t index = sc_hash(data.key);

    for (SCNode *current = table->buckets[index]; current != NULL; current = current->next) {
        if (current->data.key == data.key) {
            return false;
        }
    }
    SCNode *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return false;
    }
    new_node->data = data;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;

    return true;
}
bool sc_delete(SCHashTable *table, int key, SCItem *data)
{
    if (table == NULL || data == NULL) {
        return false;
    }
    size_t index = sc_hash(key);
    SCNode *prev = NULL;
    SCNode *target = table->buckets[index];

    while (target != NULL) {
        if (target->data.key == key) {
            if (prev == NULL) {
                table->buckets[index] = target->next;
            } else {
                prev->next = target->next;
            }
            *data = target->data;
            free(target);
            return true;
        }
        prev = target;
        target = target->next;
    }
    return false;
}
bool sc_search(SCHashTable *table, int key, SCItem *data)
{
    if (table == NULL || data == NULL) {
        return false;
    }
    size_t index = sc_hash(key);

    for (const SCNode *current = table->buckets[index]; current != NULL; current = current->next) {
        if (current->data.key == key) {
            *data = current->data;
            return true;
        }
    }
    return false;
}
// void printBuckets(void)
//{
//     for (int i = 0; i < CAPACITY; i++) {
//         printf("bucket %d:", i);
//         for (Entry *e = buckets[i]; e != NULL; e = e->next) {
//             printf(" (%s=%d)", e->key, e->value);
//         }
//         printf("\n");
//     }
// }