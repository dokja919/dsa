#include "a_v_l_tree.h"
#include "binary_search_tree.h"
#include "red_black_tree.h"
#include <stdio.h>

void bs_test(void)
{
    BSOrderedSet *os = bs_create();
    int keys[] = {10, 20, 30, 40, 50, 25};
    BSItem data;

    for (int i = 0; i < 6; i++) {
        data.key = keys[i];
        bs_insert(os, data);
    }
    bs_print(os);

    if (bs_search(os, 40, &data)) {
        printf("key: %d\n", data.key);
    }
    printf("after removing 30: ");
    if (bs_delete(os, 30, &data)) {
        printf("data: %d\n", data.key);
    }
    bs_print(os);

    bs_destroy(os);
}
void avl_test(void)
{
    AVLOrderedSet *os = avl_create();
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int i = 0; i < 6; i++) {
        avl_insert(os, keys[i]);
    }
    avl_print(os);

    printf("after removing 30\n");
    avl_delete(os, 30);
    avl_print(os);

    avl_destroy(os);
}
void rb_test(void)
{
    RBOrderedSet *os = rb_create();
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int i = 0; i < 6; i++) {
        rb_insert(os, keys[i]);
    }
    rb_print(os);

    printf("after removing 30\n");
    rb_delete(os, 30);
    rb_print(os);

    rb_destroy(os);
}
int main(void)
{
    int os_number = 0;

    switch (os_number) {
    case 0:
        bs_test();
        break;
    case 1:
        avl_test();
        break;
    case 2:
        rb_test();
        break;
    }
    return 0;
}
