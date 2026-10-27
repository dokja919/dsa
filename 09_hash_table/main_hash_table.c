#include "direct_address_table.h"
#include "s_c_hash_table.h"
#include <stdio.h>

void dat_test(void)
{
    DATItem item = {.key = 3};
    DATItem data;

    DATable *table = dat_create();
    if (table == NULL) {
        return;
    }
    printf("Insert: %s\n", dat_insert(table, item) ? "PASS" : "FAIL");

    item = (DATItem){.key = 7};
    printf("Insert: %s\n", dat_insert(table, item) ? "PASS" : "FAIL");

    if (dat_search(table, 3, &data)) {
        printf("Found data: %zu\n", data.key);
    }

    printf("Delete: %s\n", dat_delete(table, 3, &data) ? "PASS" : "FAIL");

    if (dat_search(table, 3, &data)) {
        puts("Unexpectedly found deleted item");
    } else {
        puts("Not found after deletion");
    }

    dat_destroy(table);

    // DATItem table[DAT_CAPACITY] = {0};
    // int value;

    // if (!dat_insert(table, 3, 300) || !dat_insert(table, 7, 700)) {
    //     return;
    // }

    // if (dat_search(table, 3, &value)) {
    //     printf("value = %d\n", value);
    // } else {
    //     printf("data is empty.\n");
    // }

    // dat_delete(table, 3);

    // if (dat_search(table, 3, &value)) {
    //     printf("value = %d\n", value);
    // } else {
    //     printf("data is empty.\n");
    // }

    // dat_delete(table, 7);
}

void sc_test(void)
{
    SCHashTable *table = sc_create();
    SCItem item = {.key = 10};
    SCItem data;

    if (table == NULL) {
        puts("Table creation failed");
        return 1;
    }

    printf("Insert: %s\n", sc_insert(table, item) ? "PASS" : "FAIL");

    if (sc_search(table, 10, &data)) {
        printf("Found key: %d\n", data.key);
    } else {
        puts("Not found");
    }

    printf("Delete: %s\n", sc_delete(table, 10, &data) ? "PASS" : "FAIL");

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
