#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int key;
} BSItem;
typedef struct BSNode* BSIter;
typedef struct BinarySearchTree BSOrderedSet;

BSOrderedSet* bs_create(void);
void bs_destroy(BSOrderedSet* tree);
bool bs_insert(BSOrderedSet* tree, BSItem data);
bool bs_search(BSOrderedSet* tree, int key, BSIter* out_iter);
bool bs_delete(BSOrderedSet* tree, int key, BSItem* out_data);
bool bs_delete_iter(BSOrderedSet* tree, BSIter target, BSItem* out_data);
void bs_print(BSOrderedSet* tree);
BSItem bs_get(BSIter iter);

#endif
