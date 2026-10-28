#ifndef DIRECT_ADDRESS_TABLE_H
#define DIRECT_ADDRESS_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct DATItem {
    size_t key;
} DATItem;
typedef struct DATable DATable;

DATable *dat_create(void);
void dat_destroy(DATable *table);
bool dat_insert(DATable *table, DATItem data);
bool dat_delete(DATable *table, size_t key, DATItem *data);
bool dat_search(DATable *table, size_t key, DATItem *data);

#endif