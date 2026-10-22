#include "array_binary_tree.h"
#include "linked_binary_tree.h"
#include <stdio.h>

void a_test(void)
{
    ABinaryTree *tree = a_create();

    int values[] = {10, 20, 30, 40, 50, 60, 70};
    for (int i = 0; i < 7; i++) {
        a_insert(tree, values[i]);
    }

    a_print(tree);

    printf("\n");
    printf("left of 20: %d\n", a_get_left(tree, 1));

    printf("right of 20: %d\n", a_get_right(tree, 1));

    printf("parent of 50: %d\n", a_get_parent(tree, 4));

    a_destroy(tree);
}

void l_test(void)
{
    LNode *root = l_node_create(1);

    LNode *B = l_set_left(root, 2);
    LNode *C = l_set_left(B, 3);
    LNode *D = l_set_right(B, 4);
    LNode *E = l_set_right(root, 5);
    LNode *F = l_set_left(E, 6);
    LNode *G = l_set_right(E, 7);

    // 트리 출력
    printf("Preorder ...\n");
    l_preorder(root);
    printf("\n\n");

    printf("Inorder ... \n");
    l_inorder(root);
    printf("\n\n");

    printf("Postorder ... \n");
    l_postorder(root);
    printf("\n");
}
int main(void)
{
    int bt_number = 1;

    switch (bt_number) {
    case 0:
        a_test();
        break;
    case 1:
        l_test();
        break;
    }
    return 0;
}