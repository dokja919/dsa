#ifndef DOUBLE_HASHING_HASH_TABLE_H
#define DOUBLE_HASHING_HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int key;
} DHItem;
typedef struct DoubleHashingHashTable DHSet;

DHSet* dh_create(void);
void dh_destroy(DHSet* table);
bool dh_search(DHSet* table, int key, size_t* index_out, DHItem* data_out);
bool dh_insert(DHSet* table, DHItem data);
bool dh_delete_at(DHSet* table, size_t index, DHItem* data_out);
bool dh_delete(DHSet* table, int key, DHItem* data_out);

#endif // !DOUBLE_HASHING_HASH_TABLE_H
