#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _dl_node {
    DLItem data;
    struct _dl_node *next;
    struct _dl_node *prev;
} dl_node;

struct DoublyLinkedList {
    dl_node *head_sentinel;
    dl_node *tail_sentinel;
    size_t size;
};

static dl_node *dl_node_create(int value)
{
    dl_node *new_node = malloc(sizeof(*new_node));
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

    list->head_sentinel = dl_node_create(0);
    if (list->head_sentinel == NULL) {
        free(list);
        return NULL;
    }
    list->tail_sentinel = dl_node_create(0);
    if (list->tail_sentinel == NULL) {
        free(list->head_sentinel);
        free(list);
        return NULL;
    }

    list->size = 0;
    list->head_sentinel->next = list->tail_sentinel;
    list->tail_sentinel->prev = list->head_sentinel;

    return list;
}
static dl_node *dl_node_get(DLList *list, size_t pos)
{
    if (list == NULL || pos > list->size) {
        return NULL;
    }
    if (pos == list->size) {
        return list->tail_sentinel;
    }
    dl_node *target = NULL;

    if (pos < list->size / 2) {
        target = list->head_sentinel->next;

        for (size_t i = 0; i < pos; i++) {
            target = target->next;
        }
    } else {
        target = list->tail_sentinel->prev;

        for (size_t i = list->size - 1; i > pos; i--) {
            target = target->prev;
        }
    }

    return target;
}
void dl_insert_at(DLList *list, size_t pos, int value)
{
    if (list == NULL || pos > list->size) {
        return;
    }

    dl_node *new_node = dl_node_create(value);
    if (new_node == NULL) {
        return;
    }

    dl_node *next = dl_node_get(list, pos);

    next->prev->next = new_node;
    new_node->prev = next->prev;

    new_node->next = next;
    next->prev = new_node;

    list->size++;
}
DLItem dl_delete_at(DLList *list, size_t pos)
{
    if (list == NULL || pos >= list->size) {
        return 0;
    }

    dl_node *target = dl_node_get(list, pos);
    if (target == NULL) {
        return 0;
    }

    target->prev->next = target->next;
    target->next->prev = target->prev;

    DLItem data = target->data;
    free(target);
    list->size--;
    return data;
}
void dl_destroy(DLList *list)
{
    if (list == NULL) {
        return;
    }

    while (list->size > 0) {
        dl_delete_at(list, 0);
    }

    free(list->head_sentinel);
    free(list->tail_sentinel);
    free(list);
}
DLItem dl_get(DLList *list, size_t pos)
{
    if (list == NULL || pos >= list->size) {
        return 0;
    }

    return dl_node_get(list, pos)->data;
}
void dl_print(DLList *list)
{
    if (list == NULL || list->head_sentinel == NULL) {
        return;
    }
    dl_node *current = list->head_sentinel->next;

    while (current != list->tail_sentinel) {
        printf("<- %d ->", current->data);
        current = current->next;
    }
    printf("\n");
}
size_t dl_size(DLList *list)
{
    return list ? list->size : 0;
}
// static dl_node *dl_search(DLList *list, int key)
//{
//     if (list == NULL) {
//         return NULL;
//     }
//     dl_node *target = list->head_sentinel->next;
//
//     while (target != list->tail_sentinel) {
//         if (target->data == key) {
//             return target;
//         }
//         target = target->next;
//     }
//     return NULL;
// }
//  static void dl_node_insert(DLList *list, dl_node *prev, dl_node *node)
//{
//      if (list == NULL || prev == NULL || node == NULL) {
//          return;
//      }
//      node->next = prev->next;
//      prev->next->prev = node;
//      prev->next = node;
//      node->prev = prev;
//      list->size++;
//  }
//  static void dl_node_delete(DLList *list, dl_node *node)
//{
//     if (list == NULL || node == NULL) {
//         return;
//     }
//     node->prev->next = node->next;
//     node->next->prev = node->prev;
//     dl_node_destroy(node);
//     list->size--;
// }