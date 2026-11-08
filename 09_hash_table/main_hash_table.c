#include "l_p_hash_table.h"
#include "s_c_hash_table.h"
#include <stdio.h>

void sc_test(void)
{
    SCSet* table = sc_create();
    if (table == NULL) {
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
        bool found = sc_search(table, keys[i], &iter, &data);

        if (found) {
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
           sc_search(table, 42, NULL, NULL) ? "FAIL" : "PASS");

    printf("\n--- Delete by iterator ---\n");
    SCIter iter = NULL;
    if (sc_search(table, 58, &iter, &data) && sc_delete_iter(table, iter, &data)) {
        printf("Delete key 58 by iterator: PASS (deleted %d)\n", data.key);
    } else {
        printf("Delete key 58 by iterator: FAIL\n");
    }

    sc_destroy(table);
}
void lp_test(void)
{
    LPSet* table = lp_create();
    if (table == NULL) {
        return;
    }
    int keys[] = { 12, 20, 28, 35 };
    size_t item_count = sizeof(keys) / sizeof(keys[0]);
    size_t index;
    LPItem data;

    for (size_t i = 0; i < item_count; i++) {
        data.key = keys[i];
        lp_insert(table, data);
    }
    printf("\n=== Search ===\n");

    if (lp_search(table, 22, &index, &data)) {
        printf("Found: key = 22\n");
    }
    if (lp_search(table, 28, &index, &data)) {
        printf("Found: key = 28\n");
    }
    if (lp_search(table, 20, &index, &data)) {
        printf("Found: key = 20\n");
    }
    printf("\n=== Delete ===\n");
    if (lp_delete(table, 20, &data)) {
        printf("Key 20 deleted.\n");
    }
    printf("Search key 28 after deleting 20: %s\n",
           lp_search(table, 28, NULL, NULL) ? "PASS" : "FAIL");

    printf("Search deleted key 20: %s\n",
           !lp_search(table, 20, NULL, NULL) ? "PASS" : "FAIL");
    lp_destroy(table);
}
int main(void)
{
    size_t table_number = 1;

    switch (table_number) {
    case 0:
        sc_test();
        break;
    case 1:
        lp_test();
        break;
    }
    return 0;
}
