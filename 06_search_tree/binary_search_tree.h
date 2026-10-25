#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int key;
} BSItem;
typedef struct BinarySearchTree BSOrderedSet;

BSOrderedSet *bs_create(void);
void bs_destroy(BSOrderedSet *tree);
bool bs_insert(BSOrderedSet *tree, BSItem data);
bool bs_delete(BSOrderedSet *tree, int key);
bool bs_search(BSOrderedSet *tree, int key, BSItem *data);
void bs_get(BSItem data);
void bs_print(BSOrderedSet *tree);

#endif
