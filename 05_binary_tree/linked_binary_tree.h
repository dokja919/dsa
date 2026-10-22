#ifndef LINKED_BINARY_TREE_H
#define LINKED_BINARY_TREE_H

#include <stddef.h>

typedef int LItem;
typedef struct LNode LNode;
typedef struct LinkedBinaryTree LBinaryTree;

LNode *l_set_left(LNode *parent, int value);
LNode *l_set_right(LNode *parent, int value);
LNode *l_get_left(LNode *node);
LNode *l_get_right(LNode *node);
int l_get(LNode *node);
void l_preorder(LNode *node);
void l_inorder(LNode *node);
void l_postorder(LNode *node);

void l_subtree_destroy(LNode *node);
LNode *l_node_create(int value);
void l_node_destroy(LNode *node);

#endif