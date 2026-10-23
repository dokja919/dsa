#include "direct_address_table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool dat_insert(DATItem table[], size_t key, int value)
{
    if (table == NULL || key >= DAT_CAPACITY) {
        return false;
    }
    table[key].value = value;
    table[key].occupied = true;

    return true;
}
bool dat_search(DATItem table[], size_t key, int *value)
{
    if (table == NULL || value == NULL || key >= DAT_CAPACITY || !table[key].occupied) {
        return false;
    }
    *value = table[key].value;

    return true;
}
bool dat_delete(DATItem table[], size_t key)
{
    if (table == NULL || key >= DAT_CAPACITY || !table[key].occupied) {
        return false;
    }
    table[key].occupied = false;

    return true;
}