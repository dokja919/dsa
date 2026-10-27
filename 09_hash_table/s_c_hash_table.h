#ifndef S_C_HASH_TABLE_H
#define S_C_HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int key;
} SCItem;
typedef struct SCHashTable SCHashTable;

SCHashTable *sc_create(void);
void sc_destroy(SCHashTable *table);
size_t sc_hash(int key);
bool sc_insert(SCHashTable *table, SCItem data);
bool sc_delete(SCHashTable *table, int key, SCItem *data);
bool sc_search(SCHashTable *table, int key, SCItem *data);

#endif