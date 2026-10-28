#include "direct_address_table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { DAT_CAPACITY = 16 };

struct DATable {
    DATItem *items[DAT_CAPACITY];
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
    for (size_t i = 0; i < DAT_CAPACITY; i++) {
        free(table->items[i]);
    }
    free(table);
}
bool dat_insert(DATable *table, DATItem data)
{
    if (table == NULL || data.key >= DAT_CAPACITY) {
        return false;
    }
    if (table->items[data.key] != NULL) {
        *table->items[data.key] = data;
        return true;
    }
    DATItem *item = malloc(sizeof(*item));
    if (item == NULL) {
        return false;
    }
    *item = data;

    table->items[data.key] = item;

    return true;
}
bool dat_search(DATable *table, size_t key, DATItem *data)
{
    if (table == NULL || data == NULL || key >= DAT_CAPACITY || table->items[key] == NULL) {
        return false;
    }
    *data = *table->items[key];

    return true;
}
bool dat_delete(DATable *table, size_t key, DATItem *data)
{
    if (table == NULL || data == NULL || key >= DAT_CAPACITY || table->items[key] == NULL) {
        return false;
    }
    *data = *table->items[key];
    free(table->items[key]);
    table->items[key] = NULL;

    return true;
}