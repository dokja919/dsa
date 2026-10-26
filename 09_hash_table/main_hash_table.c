#include "direct_address_table.h"
#include "s_c_hash_table.h"
#include <stdio.h>

void dat_test(void)
{
    DATItem table[DAT_CAPACITY] = {0};
    int value;

    if (!dat_insert(table, 3, 300) || !dat_insert(table, 7, 700)) {
        return;
    }

    if (dat_search(table, 3, &value)) {
        printf("value = %d\n", value);
    } else {
        printf("data is empty.\n");
    }

    dat_delete(table, 3);

    if (dat_search(table, 3, &value)) {
        printf("value = %d\n", value);
    } else {
        printf("data is empty.\n");
    }

    dat_delete(table, 7);
}

void sc_test(void)
{
    SCHashTable *table = sc_create();
    SCItem item;

    if (table == NULL) {
        puts("Table creation failed");
        return;
    }

    printf("Hash collision: %s\n",
           sc_hash(12) == sc_hash(28) && sc_hash(28) == sc_hash(44) ? "PASS" : "FAIL");

    printf("Insert: %s\n", sc_insert(table, 12) && sc_insert(table, 28) && sc_insert(table, 44) &&
                                   sc_insert(table, -1) && !sc_insert(table, 28)
                               ? "PASS"
                               : "FAIL");

    int search_ok = 0;
    if (sc_search(table, 28, &item)) {
        printf("Found key: %d\n", item.key);
        search_ok = item.key == 28 && !sc_search(table, 99, &item);
    }
    printf("Search: %s\n", search_ok ? "PASS" : "FAIL");

    printf("Delete: %s\n", sc_delete(table, 28) && !sc_search(table, 28, &item) &&
                                   sc_delete(table, 44) && sc_delete(table, 12) &&
                                   sc_delete(table, -1) && !sc_delete(table, 12)
                               ? "PASS"
                               : "FAIL");

    printf("Negative key hash: %s\n", sc_hash(-1) == sc_hash(15) ? "PASS" : "FAIL");

    sc_destroy(table);
}

int main(void)
{
    size_t table_number = 1;

    switch (table_number) {
    case 0:
        dat_test();
        break;
    case 1:
        sc_test();
        break;
    }

    return 0;
}
