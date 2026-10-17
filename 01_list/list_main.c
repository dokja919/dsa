#include "array_list.h"
#include "circular_doubly_linked_list.h"
#include "circular_linked_list.h"
#include "doubly_linked_list.h"
#include "singly_linked_list.h"
#include <stdio.h>

void a_test(void)
{
    AList *list = a_create();
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < 5; i++) {
        a_insert_at(list, a_size(list), i);
    }
    a_insert_at(list, a_size(list), -1);
    a_insert_at(list, a_size(list), -2);
    a_print(list);

    printf("\nInserting 3000 At [2]...\n\n");
    a_insert_at(list, 2, 3000);
    a_print(list);

    printf("\nRemoving Node at [2]...\n\n");
    a_delete_at(list, 2);
    a_print(list);

    a_destroy(list);
}
void sl_test(void)
{
    SLList *list = sl_create();
    if (list == NULL) {
        return;
    }
    for (int i = 5; i > 0; i--) {
        sl_insert_at(list, sl_size(list), i);
    }
    sl_insert_at(list, sl_size(list), -1);
    sl_insert_at(list, sl_size(list), -2);

    sl_print(list);

    printf("\nInserting 3000 At [2]...\n\n");
    sl_insert_at(list, 2, 3000);

    sl_print(list);

    printf("\nDestroying List...\n");
    sl_destroy(list);
}
void cl_test(void)
{
    CLList *list = cl_create();
    if (list == NULL) {
        return;
    }
    for (int i = 5; i > 0; i--) {
        cl_insert_at(list, cl_size(list), i);
    }
    cl_insert_at(list, cl_size(list), -1);
    cl_insert_at(list, cl_size(list), -2);

    cl_print(list);

    printf("\nInserting 3000 At [2]...\n\n");
    cl_insert_at(list, 2, 3000);

    cl_print(list);

    printf("\nDestroying List...\n");
    cl_destroy(list);
}
void dl_test(void)
{
    DLList *list = dl_create();
    if (list == NULL) {
        return;
    }
    for (int i = 5; i > 0; i--) {
        dl_insert_at(list, dl_size(list), i);
    }
    dl_insert_at(list, dl_size(list), -1);
    dl_insert_at(list, dl_size(list), -2);

    dl_print(list);

    printf("\nInserting 3000 At [2]...\n\n");
    dl_insert_at(list, 2, 3000);

    dl_print(list);

    printf("\nDestroying List...\n");
    dl_destroy(list);
}
void cdl_test(void)
{
    int value;
    CDLList *list = cdl_create();
    if (list == NULL) {
        return;
    }
    for (int i = 1; i <= 5; i++) {
        cdl_insert_at(list, cdl_size(list), i * 10);
    }
    cdl_insert_at(list, 0, 5);
    cdl_insert_at(list, 3, 25);

    cdl_print(list);

    if (cdl_get(list, 3, &value)) {
        printf("Get [3]: %d\n", value);
    }
    if (cdl_delete_at(list, 3, &value)) {
        printf("Delete [3]: %d\n", value);
    }

    cdl_print(list);
    printf("Size: %zu\n", cdl_size(list));

    cdl_destroy(list);
}
int main(void)
{
    int list_number = 4;

    switch (list_number) {
    case 0:
        a_test();
        break;
    case 1:
        sl_test();
        break;
    case 2:
        cl_test();
        break;
    case 3:
        dl_test();
        break;
    case 4:
        cdl_test();
        break;
    }
    return 0;
}
