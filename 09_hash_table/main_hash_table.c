#include "d_h_hash_table.h"
#include "l_p_hash_table.h"
#include "q_p_hash_table.h"
#include "s_c_hash_table.h"
#include <stdio.h>

static int keys[] = { 10, 26, 42, 58, 11, 27, 43, 59, 12, 28 };
static size_t size = sizeof(keys) / sizeof(keys[0]);

void sc_test(void)
{
    SCSet* table = sc_create();
    if (table == NULL) {
        return;
    }
    SCItem data;

    printf("=== Separate Chaining Hash Table ===\n");

    for (size_t i = 0; i < size; ++i) {
        SCItem item = { .key = keys[i] };
        bool inserted = sc_insert(table, item);
        printf("Insert key %d: %s\n", keys[i], inserted ? "PASS" : "FAIL");

        if (!inserted) {
            sc_destroy(table);
            return;
        }
    }
    printf("\n--- Search ---\n");
    for (size_t i = 0; i < size; ++i) {
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
    size_t index;
    LPItem data;

    for (size_t i = 0; i < size; i++) {
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
void qp_test(void)
{
    QPSet* table = qp_create();
    if (table == NULL) {
        printf("Quadratic Probing: create failed.\n");
        return;
    }
    QPItem data;
    size_t index = 0;

    printf("\n=== Quadratic Probing Hash Table ===\n");
    printf("--- Insert ---\n");
    for (size_t i = 0; i < size; ++i) {
        QPItem item = { .key = keys[i] };
        print_result("Insert key", keys[i], qp_insert(table, item));
    }

    printf("\n--- Search ---\n");
    for (size_t i = 0; i < size; ++i) {
        bool found = qp_search(table, keys[i], NULL, &data);
        print_result("Search key", keys[i], found && data.key == keys[i]);
    }

    printf("\n--- Delete by key ---\n");
    bool deleted = qp_delete(table, 42, &data);
    print_result("Delete key", 42, deleted && data.key == 42);
    print_result("Search deleted key", 42,
                 !qp_search(table, 42, NULL, NULL));

    printf("\n--- Delete by index ---\n");
    bool found = qp_search(table, 58, &index, NULL);
    deleted = found && qp_delete_at(table, index, &data);
    print_result("Delete key by index", 58, deleted && data.key == 58);
    print_result("Search deleted key", 58,
                 !qp_search(table, 58, NULL, NULL));

    qp_destroy(table);
}
void dh_test(void)
{
    DHSet* table = dh_create();
    if (table == NULL) {
        return;
    }
    size_t index;
    DHItem data;

    for (size_t i = 0; i < size; i++) {
        data.key = keys[i];
        dh_insert(table, data);
    }

    if (dh_search(table, 23, &index, &data)) {
        printf("Found: key = 23\n");
    }

    if (lp_delete(table, 5, &data)) {
        printf("Key 5 deleted.\n");
    }
    dh_destroy(table);
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
    case 2:
        qp_test();
        break;
    case 3:
        dh_test();
        break;
    }
    return 0;
}
