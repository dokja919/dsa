#include "a_v_l_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} AVLItem;

struct AVLNode {
    AVLItem data;
    size_t height;
    struct AVLNode* left;
    struct AVLNode* right;
};
struct AVLTree {
    AVLNode* root;
};

AVLOrderedSet* avl_create(void)
{
    AVLOrderedSet* tree = malloc(sizeof(*tree));
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;

    return tree;
}
static void subtree_destroy(AVLNode* subtree)
{
    if (subtree == NULL) {
        return;
    }
    subtree_destroy(subtree->left);
    subtree_destroy(subtree->right);
    free(subtree);
}
void avl_destroy(AVLOrderedSet* tree)
{
    if (tree == NULL) {
        return;
    }
    subtree_destroy(tree->root);
    free(tree);
}
static AVLNode* node_create(int key)
{
    AVLNode* new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data.key = key;
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
static size_t get_height(AVLNode* node)
{
    return node ? node->height : 0;
}
static void update_height(AVLNode* node)
{
    if (node == NULL) {
        return;
    }
    size_t left = get_height(node->left);
    size_t right = get_height(node->right);
    node->height = 1 + (left > right ? left : right);
}
static AVLNode* rotate_left(AVLNode* x)
{
    if (x == NULL) {
        return NULL;
    }
    AVLNode* y = x->right;
    x->right = y->left;
    y->left = x;
    update_height(x);
    update_height(y);
    return y;
}
static AVLNode* rotate_right(AVLNode* y)
{
    if (y == NULL) {
        return NULL;
    }
    AVLNode* x = y->left;
    y->left = x->right;
    x->right = y;
    update_height(y);
    update_height(x);
    return x;
}
static int balancefactor(AVLNode* node)
{
    int left = (int)get_height(node->left);
    int right = (int)get_height(node->right);
    return left - right;
}
static AVLNode* rebalance(AVLNode* node)
{
    if (node == NULL) {
        return NULL;
    }
    update_height(node);
    int balance = balancefactor(node);

    if (balance > 1) {
        if (balancefactor(node->left) < 0) {
            node->left = rotate_left(node->left);
        }

        return rotate_right(node);
    }
    if (balance < -1) {

        if (balancefactor(node->right) > 0) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }
    return node;
}
static AVLNode* node_insert(AVLNode* node, int key)
{
    if (node == NULL) {
        return node_create(key);
    }
    if (key < node->data.key) {
        node->left = node_insert(node->left, key);
    } else if (key > node->data.key) {
        node->right = node_insert(node->right, key);
    } else {
        return node;
    }
    return rebalance(node);
}
void avl_insert(AVLOrderedSet* tree, int key)
{
    if (tree == NULL) {
        return;
    }
    tree->root = node_insert(tree->root, key);
}
static AVLNode* get_min(AVLNode* node)
{
    if (node == NULL) {
        return NULL;
    }
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}
static AVLNode* node_delete(AVLNode* node, int key)
{
    if (node == NULL) {
        return NULL;
    }

    if (key < node->data.key) {
        node->left = node_delete(node->left, key);
    } else if (key > node->data.key) {
        node->right = node_delete(node->right, key);
    } else {
        if (node->left == NULL || node->right == NULL) {
            AVLNode* child = NULL;
            if (node->left) {
                child = node->left;
            } else {
                child = node->right;
            }
            free(node);
            return child;
        }
        AVLNode* successor = get_min(node->right);
        node->data.key = successor->data.key;
        node->right = node_delete(node->right, successor->data.key);
    }

    return rebalance(node);
}
void avl_delete(AVLOrderedSet* tree, int key)
{
    if (tree == NULL) {
        return;
    }
    tree->root = node_delete(tree->root, key);
}
AVLNode* avl_search(AVLOrderedSet* tree, int key)
{
    if (tree == NULL) {
        return NULL;
    }
    AVLNode* target = tree->root;
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
int avl_get(AVLNode* node)
{
    if (node == NULL) {
        return 0;
    }
    return node->data.key;
}
static void inorder(AVLNode* node)
{
    if (node == NULL) {
        return;
    }
    inorder(node->left);
    printf("%d ", node->data.key);
    inorder(node->right);
}
void avl_print(AVLOrderedSet* tree)
{
    if (tree == NULL || tree->root == NULL) {
        return;
    }
    inorder(tree->root);
    printf("\n");
}