#include "direct_address_table.h"
#include "s_c_hash_table.h"
#include <stdio.h>

void dat_test(void)
{
    DATSet *table = dat_create();
    if (table == NULL) {
        return;
    }
    DATItem item = {.key = 3};
    DATItem data;

    printf("DAT insert (key 3): %s\n", dat_insert(table, item) ? "PASS" : "FAIL");

    item = (DATItem){.key = 7};
    printf("DAT insert (key 7): %s\n", dat_insert(table, item) ? "PASS" : "FAIL");

    if (dat_search(table, 3, &data)) {
        printf("DAT found key: %zu\n", data.key);
    }
    printf("DAT delete (key 3): %s\n", dat_delete(table, 3, &data) ? "PASS" : "FAIL");

    dat_destroy(table);
}
void sc_test(void)
{
    SCSet *table = sc_create();
    if (table == NULL) {
        return;
    }
    SCItem data;
    SCItem item = {.key = 10};

    printf("Insert: %s\n", sc_insert(table, item) ? "PASS" : "FAIL");
    if (sc_search(table, 10, &data)) {
        printf("Found key: %d\n", data.key);
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
