#ifndef QUADRATIC_PROBING_HASH_TABLE_H
#define QUADRATIC_PROBING_HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int key;
} QPItem;
typedef struct QuadraticProbingHashTable QPSet;

QPSet* qp_create(void);
void qp_destroy(QPSet* table);
bool qp_insert(QPSet* table, QPItem data);
bool qp_search(QPSet* table, int key, size_t* index_out, QPItem* data_out);
bool qp_delete_at(QPSet* table, size_t index_out, QPItem* data_out);
bool qp_delete(QPSet* table, int key, QPItem* data_out);

#endif /* QUADRATIC_PROBING_HASH_TABLE_H */
