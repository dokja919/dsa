#ifndef LINEAR_PROBING_HASH_TABLE_H
#define LINEAR_PROBING_HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int key;
} LPItem;
typedef struct LinearProbingHashTable LPSet;

LPSet* lp_create(void);
void lp_destroy(LPSet* table);
bool lp_insert(LPSet* table, LPItem data);
bool lp_search(LPSet* table, int key, size_t* index_out, LPItem* data_out);
bool lp_delete_at(LPSet* table, size_t index_out, LPItem* data_out);
bool lp_delete(LPSet* table, int key, LPItem* data_out);

#endif // !LINEAR_PROBING_HASH_TABLE_H
