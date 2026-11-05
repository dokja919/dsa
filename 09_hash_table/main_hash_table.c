#include "s_c_hash_table.h"
#include <stdio.h>

void sc_test(void)
{
    SCSet *table = sc_create();
    if (table == NULL) {
        return;
    }
    SCItem data;
    SCItem item = { .key = 10 };

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
