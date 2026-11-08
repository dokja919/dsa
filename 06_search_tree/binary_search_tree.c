#include "binary_search_tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BSNode {
    BSItem data;
    struct BSNode* parent;
    struct BSNode* left;
    struct BSNode* right;
} BSNode;

struct BinarySearchTree {
    BSNode* root;
};

BSOrderedSet* bs_create(void)
{
    BSOrderedSet* tree = malloc(sizeof(*tree));
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;

    return tree;
}
static void subtree_destroy(BSNode* root)
{
    if (root == NULL) {
        return;
    }
    BSNode* stop = root->parent;

    while (root != stop) {

        if (root->left != NULL) {
            root = root->left;
        } else if (root->right != NULL) {
            root = root->right;
        } else {
            BSNode* parent = root->parent;

            if (parent != NULL) {

                if (parent->left == root) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
            }
            free(root);
            root = parent;
        }
    }
}
void bs_destroy(BSOrderedSet* tree)
{
    if (tree == NULL) {
        return;
    }
    subtree_destroy(tree->root);
    free(tree);
}
static BSNode* node_create(BSItem data)
{
    BSNode* new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
bool bs_insert(BSOrderedSet* tree, BSItem data)
{
    if (tree == NULL) {
        return false;
    }
    BSNode* parent = NULL;
    BSNode* current = tree->root;

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
    BSNode* new_node = node_create(data);
    if (new_node == NULL) {
        return false;
    }
    new_node->parent = parent;

    if (parent == NULL) {
        tree->root = new_node;
    } else if (data.key < parent->data.key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    return true;
}
static void transplant(BSOrderedSet* tree, BSNode* old_child, BSNode* new_child)
{
    BSNode* parent = old_child->parent;

    if (parent == NULL) {
        tree->root = new_child;
    } else if (old_child == parent->left) {
        parent->left = new_child;
    } else {
        parent->right = new_child;
    }
    if (new_child != NULL) {
        new_child->parent = parent;
    }
}
bool bs_search(BSOrderedSet* tree, int key, BSIter* iter_out)
{
    if (iter_out != NULL) {
        *iter_out = NULL;
    }
    if (tree == NULL) {
        return false;
    }
    BSNode* target = tree->root;

    while (target != NULL) {

        if (key == target->data.key) {

            if (iter_out != NULL) {
                *iter_out = target;
            }
            return true;
        } else if (key < target->data.key) {
            target = target->left;
        } else {
            target = target->right;
        }
    }
    return false;
}
static bool delete_node(BSOrderedSet* tree, BSNode* target, BSItem* data_out)
{
    if (data_out != NULL) {
        *data_out = target->data;
    }
    // 2. 자식이 0개 또는 1개인 경우
    if (target->left == NULL || target->right == NULL) {
        BSNode* child = target->left ? target->left : target->right;
        transplant(tree, target, child);
        free(target);
        return true;
    }
    // 3. 두 자식이 있는 경우: 중위 후계자 탐색
    BSNode* succ = target->right;

    while (succ->left != NULL) {
        succ = succ->left;
    }
    // 4. 후계자를 원래 위치에서 분리
    if (succ->parent != target) {
        transplant(tree, succ, succ->right);

        succ->right = target->right;
        succ->right->parent = succ;
    }
    // 5. 후계자를 삭제 위치에 연결
    transplant(tree, target, succ);

    succ->left = target->left;
    succ->left->parent = succ;

    free(target);

    return true;
}
bool bs_delete(BSOrderedSet* tree, int key, BSItem* data_out)
{
    if (tree == NULL) {
        return false;
    }
    // 1. 삭제할 노드 탐색
    BSNode* target;
    if (bs_search(tree, key, &target) == false) {
        return false;
    }
    return delete_node(tree, target, data_out);
}
bool bs_delete_iter(BSOrderedSet* tree, BSIter target, BSItem* data_out)
{
    if (tree == NULL || target == NULL) {
        return false;
    }
    return delete_node(tree, target, data_out);
}
BSItem bs_get(BSIter iter)
{
    return iter->data;
}
static void inorder(BSNode* node)
{
    if (node == NULL) {
        return;
    }
    inorder(node->left);
    printf("%d ", node->data.key);
    inorder(node->right);
}
void bs_print(BSOrderedSet* tree)
{
    if (tree == NULL) {
        return;
    }
    inorder(tree->root);
    printf("\n");
}