#ifndef S_C_HASH_TABLE_H
#define S_C_HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int key;
} SCItem;

typedef struct SCNode* SCIter;
typedef struct SeparateChainingHashTable SCSet;

SCSet* sc_create(void);
void sc_destroy(SCSet* table);
size_t sc_hash(int key);
bool sc_insert(SCSet* table, SCItem data);
bool sc_search(SCSet* table, int key, SCIter* out_iter, SCItem* out_data);
bool sc_delete(SCSet* table, int key, SCItem* out_data);
bool sc_delete_iter(SCSet* table, SCIter iter, SCItem* out_data);

#endif
