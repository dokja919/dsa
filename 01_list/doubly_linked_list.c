#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct DLNode {
    DLItem data;
    struct DLNode *next;
    struct DLNode *prev;
} DLNode;

struct DoublyLinkedList {
    DLNode *head_sentinel;
    DLNode *tail_sentinel;
    size_t size;
};

static DLNode *node_create(int value)
{
    DLNode *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}
DLList *dl_create(void)
{
    DLList *list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    list->head_sentinel = node_create(0);
    if (list->head_sentinel == NULL) {
        free(list);
        return NULL;
    }
    list->tail_sentinel = node_create(0);
    if (list->tail_sentinel == NULL) {
        free(list->head_sentinel);
        free(list);
        return NULL;
    }
    list->head_sentinel->next = list->tail_sentinel;
    list->tail_sentinel->prev = list->head_sentinel;
    list->size = 0;

    return list;
}
void dl_destroy(DLList *list)
{
    if (list == NULL) {
        return;
    }
    DLNode *current = list->head_sentinel;
    while (current != NULL) {
        DLNode *next_node = current->next;
        free(current);
        current = next_node;
    }
    free(list);
}
static DLNode *node_at(DLList *list, size_t index)
{
    DLNode *target = NULL;
    if (index < list->size / 2) {
        target = list->head_sentinel->next;
        for (size_t i = 0; i < index; i++) {
            target = target->next;
        }
    } else {
        target = list->tail_sentinel;
        for (size_t i = list->size; i > index; i--) {
            target = target->prev;
        }
    }
    return target;
}
void dl_insert_at(DLList *list, size_t index, int value)
{
    if (list == NULL || index > list->size) {
        return;
    }
    DLNode *new_node = node_create(value);
    if (new_node == NULL) {
        return;
    }
    DLNode *next_node = node_at(list, index);

    next_node->prev->next = new_node;
    new_node->prev = next_node->prev;
    new_node->next = next_node;
    next_node->prev = new_node;

    list->size++;
}
DLItem dl_delete_at(DLList *list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return -1;
    }
    DLNode *target = node_at(list, index);
    target->prev->next = target->next;
    target->next->prev = target->prev;

    DLItem data = target->data;
    free(target);
    list->size--;

    return data;
}
DLItem dl_get(DLList *list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return -1;
    }
    return node_at(list, index)->data;
}
size_t dl_size(DLList *list)
{
    return list != NULL ? list->size : 0;
}
void dl_print(DLList *list)
{
    if (list == NULL || list->head_sentinel == NULL) {
        return;
    }
    DLNode *current = list->head_sentinel->next;

    while (current != list->tail_sentinel) {
        printf("<- %d ->", current->data);
        current = current->next;
    }
    printf("\n");
}