#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} BSItem;

struct BSNode {
    BSItem data;
    struct BSNode *left;
    struct BSNode *right;
};

struct BinarySearchTree {
    BSNode *root;
};

BSOrderedSet *bs_create(void)
{
    BSOrderedSet *tree = malloc(sizeof(*tree));
    if (tree == NULL) {
        return NULL;
    }

    tree->root = NULL;

    return tree;
}
static void bs_node_destroy(BSNode *node)
{
    free(node);
}
static void bs_subtree_destroy(BSNode *subtree)
{
    if (subtree == NULL) {
        return;
    }
    bs_subtree_destroy(subtree->left);
    bs_subtree_destroy(subtree->right);
    bs_node_destroy(subtree);
}
void bs_destroy(BSOrderedSet *tree)
{
    if (tree == NULL) {
        return;
    }

    bs_subtree_destroy(tree->root);
    free(tree);
}
static BSNode *bs_node_create(int key)
{
    BSNode *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data.key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
static BSNode *bs_node_insert(BSNode *node, int key)
{
    if (node == NULL) {
        return bs_node_create(key);
    }
    if (key < node->data.key) {
        node->left = bs_node_insert(node->left, key);
    } else if (key > node->data.key) {
        node->right = bs_node_insert(node->right, key);
    }
    return node;
}
void bs_insert(BSOrderedSet *tree, int key)
{
    if (tree == NULL) {
        return;
    }
    tree->root = bs_node_insert(tree->root, key);
}
static void bs_transplant(BSOrderedSet *tree, BSNode *parent, BSNode *old_subtree,
                          BSNode *new_subtree)
{
    if (parent == NULL) {
        tree->root = new_subtree;
    } else if (old_subtree == parent->left) {
        parent->left = new_subtree;
    } else {
        parent->right = new_subtree;
    }
}
void bs_delete(BSOrderedSet *tree, int key)
{
    if (tree == NULL) {
        return;
    }
    ///////////
    BSNode *target_parent = NULL;
    BSNode *target = tree->root;
    while (target && target->data.key != key) {
        target_parent = target;
        if (key < target->data.key) {
            target = target->left;
        } else {
            target = target->right;
        }
    }
    if (target == NULL) {
        return;
    }
    //////////////
    if (target->left == NULL || target->right == NULL) {
        BSNode *child = target->left ? target->left : target->right;

        bs_transplant(tree, target_parent, target, child);
        bs_node_destroy(target);
        return;
    }
    ///////////
    BSNode *succ_parent = target;
    BSNode *succ = target->right;
    while (succ->left != NULL) {
        succ_parent = succ;
        succ = succ->left;
    }
    ///////////
    if (succ != target->right) {
        bs_transplant(tree, succ_parent, succ, succ->right);
        succ->right = target->right;
    }
    bs_transplant(tree, target_parent, target, succ);
    succ->left = target->left;
    bs_node_destroy(target);
}
BSNode *bs_search(BSOrderedSet *tree, int key)
{
    if (tree == NULL) {
        return NULL;
    }
    BSNode *target = tree->root;
    while (target != NULL) {
        if (key == target->data.key) {
            return target;
        } else if (key < target->data.key) {
            target = target->left;
        } else {
            target = target->right;
        }
    }
    return NULL;
}
int bs_get(BSNode *node)
{
    if (node == NULL) {
        return 0;
    }
    return node->data.key;
}
static void bs_inorder(BSNode *node)
{
    if (node == NULL) {
        return;
    }
    bs_inorder(node->left);
    printf("%d ", node->data.key);
    bs_inorder(node->right);
}
void bs_print(BSOrderedSet *tree)
{
    if (tree == NULL || tree->root == NULL) {
        return;
    }
    bs_inorder(tree->root);
    printf("\n");
}