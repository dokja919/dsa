#include "circular_doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct CDLNode {
    CDLItem data;
    struct CDLNode *next;
    struct CDLNode *prev;
} CDLNode;

struct CircularDoublyLinkedList {
    CDLNode *sentinel;
    size_t size;
};

static CDLNode *cdl_node_create(int value)
{
    CDLNode *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}
CDLList *cdl_create(void)
{
    CDLList *list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }
    list->sentinel = cdl_node_create(0);
    if (list->sentinel == NULL) {
        free(list);
        return NULL;
    }
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
    list->size = 0;

    return list;
}
void cdl_destroy(CDLList *list)
{
    if (list == NULL) {
        return;
    }
    CDLNode *current = list->sentinel->next;
    while (current != list->sentinel) {
        CDLNode *next_node = current->next;
        free(current);
        current = next_node;
    }
    free(list->sentinel);
    free(list);
}
static bool node_valid(CDLList *list, CDLNodeHandle node)
{
    return list != NULL && node != NULL && node != list->sentinel;
}
bool cdl_insert_before(CDLList *list, CDLNodeHandle next, int value)
{
    if (node_valid(list, next) == false) {
        return false;
    }
    CDLNode *new_node = cdl_node_create(value);
    if (new_node == NULL) {
        return false;
    }
    new_node->next = next;
    new_node->prev = next->prev;
    next->prev->next = new_node;
    next->prev = new_node;
    list->size++;

    return true;
}
bool cdl_delete(CDLList *list, CDLNodeHandle target, int *value)
{
    if (node_valid(list, target) == false || value == NULL) {
        return false;
    }
    *value = target->data;
    target->prev->next = target->next;
    target->next->prev = target->prev;

    free(target);
    list->size--;

    return true;
}
bool cdl_get(CDLList *list, CDLNodeHandle node, int *value)
{
    if (node_valid(list, node) == false || value == NULL) {
        return false;
    }
    *value = node->data;

    return true;
}
bool cdl_set(CDLList *list, CDLNodeHandle node, int value)
{
    if (node_valid(list, node) == false) {
        return false;
    }
    node->data = value;

    return true;
}
CDLNodeHandle cdl_find(CDLList *list, int value)
{
    if (list == NULL) {
        return NULL;
    }
    for (CDLNode *target = list->sentinel->next; target != list->sentinel; target = target->next) {
        if (target->data == value) {
            return target;
        }
    }
    return NULL;
}
static CDLNode *node_at(CDLList *list, size_t index)
{
    CDLNode *target = NULL;
    if (index < list->size / 2) {
        target = list->sentinel->next;

        for (size_t i = 0; i < index; i++) {
            target = target->next;
        }
    } else {
        target = list->sentinel;

        for (size_t i = list->size; i > index; i--) {
            target = target->prev;
        }
    }
    return target;
}
bool cdl_insert_at(CDLList *list, size_t index, int value)
{
    if (list == NULL || index > list->size) {
        return false;
    }
    CDLNode *new_node = cdl_node_create(value);
    if (new_node == NULL) {
        return false;
    }
    CDLNode *next = node_at(list, index);

    next->prev->next = new_node;
    new_node->prev = next->prev;

    new_node->next = next;
    next->prev = new_node;

    list->size++;

    return true;
}
bool cdl_delete_at(CDLList *list, size_t index, int *value)
{
    if (list == NULL || index >= list->size || value == NULL) {
        return false;
    }
    CDLNode *target = node_at(list, index);

    target->next->prev = target->prev;
    target->prev->next = target->next;

    *value = target->data;
    free(target);
    list->size--;

    return true;
}
bool cdl_get_at(CDLList *list, size_t index, int *value)
{
    if (list == NULL || index >= list->size || value == NULL) {
        return false;
    }
    *value = node_at(list, index)->data;

    return true;
}
size_t cdl_size(CDLList *list)
{
    return list != NULL ? list->size : 0;
}
void cdl_print(CDLList *list)
{
    if (list == NULL) {
        return;
    }
    CDLNode *current = list->sentinel->next;
    while (current != list->sentinel) {
        printf("<- %d ->", current->data);
        current = current->next;
    }
    printf("<- head\n");
}