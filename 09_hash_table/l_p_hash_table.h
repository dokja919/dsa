#ifndef LINEAR_PROBING_HASH_TABLE_H
#define LINEAR_PROBING_HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef enum State LPState;
typedef struct {
    int key;
    LPState state;
} LPSlot;
typedef struct LinearProbingHashTable LPSet;

LPSet* lp_create(void);
void lp_destroy(LPSet* table);
size_t lp_hash(LPSet* table, int key);
bool lp_insert(LPSet* table, int key);
bool lp_search(LPSet* table, int key, size_t* index, LPSlot* data);
bool lp_delete(LPSet* table, int key, LPSlot* data);

#endif // !LINEAR_PROBING_HASH_TABLE_H
