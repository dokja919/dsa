#include "binary_search_tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BSNode {
    BSItem data;
    struct BSNode *left;
    struct BSNode *right;
} BSNode;

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
static void bs_subtree_destroy(BSNode *root)
{
    while (root != NULL) {
        if (root->left != NULL) {
            BSNode *left = root->left;
            root->left = left->right;
            left->right = root;
            root = left;
        } else {
            BSNode *right = root->right;
            free(root);
            root = right;
        }
    }
}
void bs_destroy(BSOrderedSet *tree)
{
    if (tree == NULL) {
        return;
    }
    bs_subtree_destroy(tree->root);
    free(tree);
}
static BSNode *bs_node_create(BSItem data)
{
    BSNode *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
bool bs_insert(BSOrderedSet *tree, BSItem data)
{
    if (tree == NULL) {
        return false;
    }
    BSNode *parent = NULL;
    BSNode *current = tree->root;
    while (current != NULL) {
        parent = current;

        if (data.key < current->data.key) {
            current = current->left;
        } else if (data.key > current->data.key) {
            current = current->right;
        } else {
            current->data = data;
            return true;
        }
    }
    BSNode *new_node = bs_node_create(data);
    if (new_node == NULL) {
        return false;
    }
    if (parent == NULL) {
        tree->root = new_node;
    } else if (data.key < parent->data.key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    return true;
}
static void bs_transplant(BSOrderedSet *tree, BSNode *parent, BSNode *old_child, BSNode *new_child)
{
    if (parent == NULL) {
        tree->root = new_child;
    } else if (old_child == parent->left) {
        parent->left = new_child;
    } else {
        parent->right = new_child;
    }
}
bool bs_delete(BSOrderedSet *tree, int key)
{
    if (tree == NULL) {
        return false;
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
        return false;
    }
    //////////////
    if (target->left == NULL || target->right == NULL) {
        BSNode *child = target->left ? target->left : target->right;

        bs_transplant(tree, target_parent, target, child);
        free(target);
        return true;
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
    free(target);

    return true;
}
bool bs_search(BSOrderedSet *tree, int key, BSItem *data)
{
    if (tree == NULL) {
        return false;
    }
    BSNode *target = tree->root;
    while (target != NULL) {
        if (key == target->data.key) {
            *data = target->data;
            return true;
        } else if (key < target->data.key) {
            target = target->left;
        } else {
            target = target->right;
        }
    }
    return false;
}
void bs_get(BSItem data)
{
    printf("-----\n");
    printf("data\n");
    printf("key: %d\n", data.key);
    printf("-----\n");
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
    if (tree == NULL) {
        return;
    }
    bs_inorder(tree->root);
    printf("\n");
}