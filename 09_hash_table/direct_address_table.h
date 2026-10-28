#ifndef DIRECT_ADDRESS_TABLE_H
#define DIRECT_ADDRESS_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t key;
} DATItem;
typedef struct DirectAddressTable DATSet;

DATSet *dat_create(void);
void dat_destroy(DATSet *table);
bool dat_insert(DATSet *table, DATItem data);
bool dat_delete(DATSet *table, size_t key, DATItem *data);
bool dat_search(DATSet *table, size_t key, DATItem *data);

#endif