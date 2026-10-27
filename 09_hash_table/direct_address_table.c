#include "direct_address_table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { DAT_CAPACITY = 16 };

struct DATable {
    DATItem items[DAT_CAPACITY];
};

DATable *dat_create(void)
{
    DATable *table = calloc(1, sizeof(*table));

    return table;
}
void dat_destroy(DATable *table)
{
    if (table == NULL) {
        return;
    }
    free(table);
}
bool dat_insert(DATItem table[], DATItem data)
{
    if (table == NULL || data.key >= DAT_CAPACITY) {
        return false;
    }
    table[data.key] = data;
    table[data.key].occupied = true;

    return true;
}
bool dat_search(DATItem table[], size_t key, DATItem *data)
{
    if (table == NULL || data == NULL || key >= DAT_CAPACITY || !table[key].occupied) {
        return false;
    }
    *data = table[key];

    return true;
}
bool dat_delete(DATItem table[], size_t key, DATItem *data)
{
    if (table == NULL || key >= DAT_CAPACITY || !table[key].occupied) {
        return false;
    }
    table[key].occupied = false;

    return true;
}