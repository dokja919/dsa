#include "linked_binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

struct LNode {
    LItem data;
    struct LNode *left;
    struct LNode *right;
};

struct LinkedBinaryTree {
    LNode *root;
};

void l_subtree_destroy(LNode *node)
{
    if (node == NULL) {
        return;
    }
    l_subtree_destroy(node->left);
    l_subtree_destroy(node->right);
    l_node_destroy(node);
}
LNode *l_node_create(int value)
{
    LNode *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
void l_node_destroy(LNode *node)
{
    free(node);
}
LNode *l_set_left(LNode *parent, int value)
{
    if (parent == NULL) {
        return NULL;
    }

    LNode *new_child = l_node_create(value);
    if (new_child == NULL) {
        return NULL;
    }

    // if (parent->left != NULL) {
    //     new_child->left = parent->left;
    // }

    parent->left = new_child;

    return new_child;
}
LNode *l_set_right(LNode *parent, int value)
{
    if (parent == NULL) {
        return NULL;
    }

    LNode *new_child = l_node_create(value);
    if (new_child == NULL) {
        return NULL;
    }

    // if (parent->right != NULL) {
    //     new_child->right = parent->right;
    // }

    parent->right = new_child;

    return new_child;
}
LNode *l_get_left(LNode *node)
{
    return node == NULL ? NULL : node->left;
}

LNode *l_get_right(LNode *node)
{
    return node == NULL ? NULL : node->right;
}

int l_get(LNode *node)
{
    return node == NULL ? 0 : node->data;
}
void l_preorder(LNode *node)
{
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    l_preorder(node->left);
    l_preorder(node->right);
}
void l_inorder(LNode *node)
{
    if (node == NULL) {
        return;
    }
    l_inorder(node->left);
    printf("%d ", node->data);
    l_inorder(node->right);
}
void l_postorder(LNode *node)
{
    if (node == NULL) {
        return;
    }
    l_postorder(node->left);
    l_postorder(node->right);
    printf("%d ", node->data);
}