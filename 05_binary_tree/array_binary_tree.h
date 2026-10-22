#ifndef ARRAY_BINARY_TREE_H
#define ARRAY_BINARY_TREE_H

#include <stdbool.h>
#include <stddef.h>

typedef int AItem;
typedef struct ArrayBinaryTree ABinaryTree;

ABinaryTree *a_create(void);
void a_destroy(ABinaryTree *tree);
void a_insert(ABinaryTree *tree, int value);
int a_get_parent(ABinaryTree *tree, size_t child);
int a_get_left(ABinaryTree *tree, size_t parent);
int a_get_right(ABinaryTree *tree, size_t parent);
void a_print(ABinaryTree *tree);
bool a_is_empty(ABinaryTree *tree);
size_t a_size(ABinaryTree *tree);

#endif