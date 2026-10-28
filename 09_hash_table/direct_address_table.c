#include "direct_address_table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { DAT_CAPACITY = 16 };

struct DirectAddressTable {
    DATItem *buckets[DAT_CAPACITY];
};

DATSet *dat_create(void)
{
    DATSet *table = calloc(1, sizeof(*table));

    return table;
}
void dat_destroy(DATSet *table)
{
    if (table == NULL) {
        return;
    }
    for (size_t i = 0; i < DAT_CAPACITY; i++) {
        free(table->buckets[i]);
    }
    free(table);
}
bool dat_insert(DATSet *table, DATItem data)
{
    if (table == NULL || data.key >= DAT_CAPACITY) {
        return false;
    }
    if (table->buckets[data.key] != NULL) {
        *table->buckets[data.key] = data;
        return true;
    }
    DATItem *item = malloc(sizeof(*item));
    if (item == NULL) {
        return false;
    }
    *item = data;

    table->buckets[data.key] = item;

    return true;
}
bool dat_search(DATSet *table, size_t key, DATItem *data)
{
    if (table == NULL || data == NULL || key >= DAT_CAPACITY || table->buckets[key] == NULL) {
        return false;
    }
    *data = *table->buckets[key];

    return true;
}
bool dat_delete(DATSet *table, size_t key, DATItem *data)
{
    if (table == NULL || data == NULL || key >= DAT_CAPACITY || table->buckets[key] == NULL) {
        return false;
    }
    *data = *table->buckets[key];
    free(table->buckets[key]);
    table->buckets[key] = NULL;

    return true;
}