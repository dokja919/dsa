#include "array_binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 32

struct ArrayBinaryTree {
    AItem *items;
    size_t capacity;
    size_t size;
};

ABinaryTree *a_create(void)
{
    ABinaryTree *tree = malloc(sizeof(*tree));
    if (tree == NULL) {
        return NULL;
    }

    size_t capacity = INITIAL_CAPACITY;
    tree->items = malloc(sizeof(*tree->items) * capacity);
    if (tree->items == NULL) {
        free(tree);
        return NULL;
    }
    tree->capacity = capacity;
    tree->size = 0;

    return tree;
}
void a_destroy(ABinaryTree *tree)
{
    if (tree == NULL) {
        return;
    }
    free(tree->items);
    free(tree);
}
void a_insert(ABinaryTree *tree, int value)
{
    if (tree == NULL) {
        return;
    }

    if (tree->size == tree->capacity) {
        return;
    }

    tree->items[tree->size] = value;
    tree->size++;
}
int a_get_parent(ABinaryTree *tree, size_t child_pos)
{
    if (a_is_empty(tree) || child_pos == 0 || child_pos >= tree->size) {
        return 0;
    }
    size_t parent_pos = (child_pos - 1) / 2;

    return tree->items[parent_pos];
}
int a_get_left(ABinaryTree *tree, size_t parent_pos)
{
    if (a_is_empty(tree) || parent_pos >= tree->size) {
        return 0;
    }
    size_t left_pos = 2 * parent_pos + 1;
    if (left_pos >= tree->size) {
        return 0;
    }
    return tree->items[left_pos];
}
int a_get_right(ABinaryTree *tree, size_t parent_pos)
{
    if (a_is_empty(tree) || parent_pos >= tree->size) {
        return 0;
    }

    size_t right_pos = 2 * parent_pos + 2;
    if (right_pos >= tree->size) {
        return 0;
    }
    return tree->items[right_pos];
}
void a_print(ABinaryTree *tree)
{
    if (tree == NULL) {
        return;
    }
    for (size_t i = 0; i < tree->size; i++) {
        printf("index %zu : %d\n", i, tree->items[i]);
    }
}
bool a_is_empty(ABinaryTree *tree)
{
    return tree == NULL || tree->size == 0;
}
size_t a_size(ABinaryTree *tree)
{
    return tree ? tree->size : 0;
}