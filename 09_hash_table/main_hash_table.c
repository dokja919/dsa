#include "s_c_hash_table.h"
#include <stdio.h>

static void sc_test(void)
{
    SCSet* table = sc_create();
    if (table == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
        return;
    }

    int keys[] = { 10, 26, 42, 58, 11, 27, 43, 59, 12, 28 };
    size_t item_count = sizeof(keys) / sizeof(keys[0]);
    SCItem data;

    printf("=== Separate Chaining Hash Table ===\n");

    for (size_t i = 0; i < item_count; ++i) {
        SCItem item = { .key = keys[i] };
        bool inserted = sc_insert(table, item);
        printf("Insert key %d: %s\n", keys[i], inserted ? "PASS" : "FAIL");

        if (!inserted) {
            sc_destroy(table);
            return;
        }
    }

    printf("\n--- Search ---\n");
    for (size_t i = 0; i < item_count; ++i) {
        SCIter iter = NULL;
        bool found = sc_search(table, keys[i], &iter);

        if (found && sc_get(iter, &data)) {
            printf("Search key %d: PASS (found %d)\n", keys[i], data.key);
        } else {
            printf("Search key %d: FAIL\n", keys[i]);
        }
    }

    printf("\n--- Delete by key ---\n");
    if (sc_delete(table, 42, &data)) {
        printf("Delete key 42: PASS (deleted %d)\n", data.key);
    } else {
        printf("Delete key 42: FAIL\n");
    }

    printf("Search deleted key 42: %s\n",
           sc_search(table, 42, NULL) ? "FAIL" : "PASS");

    printf("\n--- Delete by iterator ---\n");
    SCIter iter = NULL;
    if (sc_search(table, 58, &iter) && sc_delete_iter(table, iter, &data)) {
        printf("Delete key 58 by iterator: PASS (deleted %d)\n", data.key);
    } else {
        printf("Delete key 58 by iterator: FAIL\n");
    }

    sc_destroy(table);
}
int main(void)
{
    size_t table_number = 0;

    switch (table_number) {
    case 0:
        sc_test();
        break;
    }

    return 0;
}
