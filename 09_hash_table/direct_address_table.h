#ifndef DIRECT_ADDRESS_TABLE_H
#define DIRECT_ADDRESS_TABLE_H

#include <stdbool.h>
#include <stddef.h>

#define DAT_CAPACITY 16

typedef struct DATItem {
    size_t key;
    int value;
    bool occupied;
} DATItem;

bool dat_insert(DATItem table[], size_t key, int value);
bool dat_search(DATItem table[], size_t key, int *value);
bool dat_delete(DATItem table[], size_t key);

#endif