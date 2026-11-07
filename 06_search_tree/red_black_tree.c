#include "red_black_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    RED,
    BLACK
} RBColor;

typedef struct {
    int key;
} RBItem;

struct RBNode {
    RBItem data;
    RBColor color;
    struct RBNode* parent;
    struct RBNode* left;
    struct RBNode* right;
};
struct RedBlackTree {
    RBNode* root;
    RBNode* nil;
};

static RBNode* node_create(RBOrderedSet* tree, int key)
{
    RBNode* node = malloc(sizeof(RBNode));
    if (node == NULL) {
        return NULL;
    }

    node->data.key = key;
    node->color = RED;
    node->parent = tree->nil;
    node->left = tree->nil;
    node->right = tree->nil;

    return node;
}
RBOrderedSet* rb_create(void)
{
    RBOrderedSet* tree = malloc(sizeof(RBOrderedSet));
    if (tree == NULL) {
        return NULL;
    }

    tree->nil = malloc(sizeof(RBNode));
    if (tree->nil == NULL) {
        free(tree);
        return NULL;
    }
    tree->nil->data.key = 0;
    tree->nil->color = BLACK;
    tree->nil->parent = tree->nil;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;

    tree->root = tree->nil;

    return tree;
}
static void subtree_destroy(RBOrderedSet* tree, RBNode* node)
{
    if (node == tree->nil) {
        return;
    }
    subtree_destroy(tree, node->left);
    subtree_destroy(tree, node->right);
    free(node);
}
void rb_destroy(RBOrderedSet* tree)
{
    if (tree == NULL) {
        return;
    }
    subtree_destroy(tree, tree->root);
    free(tree->nil);
    free(tree);
}
static void rotate_left(RBOrderedSet* tree, RBNode* x)
{
    RBNode* y = x->right;

    x->right = y->left;
    if (y->left != tree->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}
static void rotate_right(RBOrderedSet* tree, RBNode* y)
{
    RBNode* x = y->left;

    y->left = x->right;
    if (x->right != tree->nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == tree->nil) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}
static void insert_fixup(RBOrderedSet* tree, RBNode* new_node)
{
    while (new_node->parent->color == RED) {
        RBNode* parent = new_node->parent;

        if (parent == parent->parent->left) {
            RBNode* uncle = parent->parent->right;
            // case 1
            if (uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                parent->parent->color = RED;
                new_node = parent->parent;
            } else {
                // case 2
                if (new_node == parent->right) {
                    new_node = parent;
                    rotate_left(tree, new_node);
                    parent = new_node->parent;
                }
                // case 3
                parent->color = BLACK;
                parent->parent->color = RED;
                rotate_right(tree, parent->parent);
            }
        } else {
            RBNode* uncle = parent->parent->left;

            if (uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                parent->parent->color = RED;
                new_node = parent->parent;
            } else {
                if (new_node == parent->left) {
                    new_node = parent;
                    rotate_right(tree, new_node);
                    parent = new_node->parent;
                }
                parent->color = BLACK;
                parent->parent->color = RED;
                rotate_left(tree, parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}
void rb_insert(RBOrderedSet* tree, int key)
{
    if (tree == NULL) {
        return;
    }
    RBNode* new_node = node_create(tree, key);
    if (new_node == NULL) {
        return;
    }

    RBNode* parent = tree->nil;
    RBNode* current = tree->root;

    while (current != tree->nil) {
        parent = current;
        if (new_node->data.key < current->data.key) {
            current = current->left;
        } else if (new_node->data.key > current->data.key) {
            current = current->right;
        } else {
            free(new_node);
            return;
        }
    }
    new_node->parent = parent;

    if (parent == tree->nil) {
        tree->root = new_node;
    } else if (new_node->data.key < parent->data.key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    insert_fixup(tree, new_node);
}
static void delete_fixup(RBOrderedSet* tree, RBNode* current)
{
    while (current != tree->root && current->color == BLACK) {
        if (current == current->parent->left) {
            RBNode* sibling = current->parent->right;
            // case 1
            if (sibling->color == RED) {
                sibling->color = BLACK;
                current->parent->color = RED;
                rotate_left(tree, current->parent);
                sibling = current->parent->right;
            }
            // case 2
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                current = current->parent;
            } else {
                // case 3
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotate_right(tree, sibling);
                    sibling = current->parent->right;
                }
                // case 4
                sibling->color = current->parent->color;
                current->parent->color = BLACK;
                sibling->right->color = BLACK;
                rotate_left(tree, current->parent);
                current = tree->root;
            }
        } else {
            RBNode* sibling = current->parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                current->parent->color = RED;
                rotate_right(tree, current->parent);
                sibling = current->parent->left;
            }

            if (sibling->right->color == BLACK &&
                sibling->left->color == BLACK) {
                sibling->color = RED;
                current = current->parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotate_left(tree, sibling);
                    sibling = current->parent->left;
                }

                sibling->color = current->parent->color;
                current->parent->color = BLACK;
                sibling->left->color = BLACK;
                rotate_right(tree, current->parent);
                current = tree->root;
            }
        }
    }
    current->color = BLACK;
}
static void transplant(RBOrderedSet* tree, RBNode* old_subtree, RBNode* new_subtree)
{
    if (old_subtree->parent == tree->nil) {
        tree->root = new_subtree;
    } else if (old_subtree == old_subtree->parent->left) {
        old_subtree->parent->left = new_subtree;
    } else {
        old_subtree->parent->right = new_subtree;
    }
    new_subtree->parent = old_subtree->parent;
}
static RBNode* get_min(RBOrderedSet* tree, RBNode* node)
{
    while (node->left != tree->nil) {
        node = node->left;
    }
    return node;
}
void rb_delete(RBOrderedSet* tree, int key)
{
    if (tree == NULL) {
        return;
    }
    RBNode* target = rb_search(tree, key);
    if (target == NULL) {
        return;
    }

    RBNode* replacement = target;
    RBColor original_color = replacement->color;
    RBNode* child = NULL;
    // case 1
    if (target->left == tree->nil || target->right == tree->nil) {
        child = target->left != tree->nil ? replacement->left : replacement->right;

        transplant(tree, replacement, child);
    } else {
        replacement = get_min(tree, target->right);
        original_color = replacement->color;
        child = replacement->right;
        // case 2
        if (replacement != target->right) {
            transplant(tree, replacement, child);

            replacement->right = target->right;
            replacement->right->parent = replacement;
        } else { // case 3
            child->parent = replacement;
        }
        transplant(tree, target, replacement);

        replacement->left = target->left;
        replacement->left->parent = replacement;

        replacement->color = target->color;
    }
    free(target);

    if (original_color == BLACK) {
        delete_fixup(tree, child);
    }
}
static RBNode* node_search(RBOrderedSet* tree, RBNode* node, int key)
{
    while (node != tree->nil) {
        if (key == node->data.key) {
            return node;
        }

        if (key < node->data.key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return NULL;
}
RBNode* rb_search(RBOrderedSet* tree, int key)
{
    if (tree == NULL) {
        return NULL;
    }
    return node_search(tree, tree->root, key);
}
int rb_get(RBNode* node)
{
    if (node == NULL) {
        return 0;
    }
    return node->data.key;
}
static void node_print(RBOrderedSet* tree, RBNode* node, size_t depth, size_t black_count)
{
    if (node == tree->nil) {
        return;
    }
    if (node->color == BLACK) {
        black_count++;
    }
    node_print(tree, node->left, depth + 1, black_count);

    int parent_key = -1;
    char position = 'X';

    if (node->parent != tree->nil) {
        parent_key = node->parent->data.key;

        if (node == node->parent->left) {
            position = 'L';
        } else {
            position = 'R';
        }
    }
    for (size_t i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%d %s [%c,%d]", node->data.key,
           node->color == RED ? "RED" : "BLACK", position, parent_key);
    if (node->left == tree->nil && node->right == tree->nil) {
        printf(" --------- %zu", black_count);
    }
    printf("\n");

    node_print(tree, node->right, depth + 1, black_count);
}
void rb_print(RBOrderedSet* tree)
{
    if (tree == NULL) {
        return;
    }
    node_print(tree, tree->root, 0, 0);
}