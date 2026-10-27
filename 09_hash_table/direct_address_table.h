#ifndef DIRECT_ADDRESS_TABLE_H
#define DIRECT_ADDRESS_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct DATItem {
    size_t key;
    bool occupied;
} DATItem;
typedef struct DATable DATable;

DATable *dat_create(void);
void dat_destroy(DATable *table);
bool dat_insert(DATItem *table, DATItem data);
bool dat_delete(DATItem *table, size_t key, DATItem *data);
bool dat_search(DATItem *table, size_t key, DATItem *data);

#endif