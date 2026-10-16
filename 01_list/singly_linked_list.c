#include "singly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

struct _sl_node {
    SLItem data;
    struct _sl_node *next;
};

struct SinglyLinkedList {
    sl_node *head;
    size_t size;
};

SLList *sl_create(void)
{
    SLList *list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    list->size = 0;
    list->head = NULL;

    return list;
}
static sl_node *sl_node_create(int value)
{
    sl_node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}
void sl_insert_at(SLList *list, size_t index, int value)
{
    if (list == NULL || index > list->size) {
        return;
    }
    sl_node *new_node = sl_node_create(value);
    if (new_node == NULL) {
        return;
    }
    if (index == 0) {
        new_node->next = list->head;
        list->head = new_node;
    } else {
        sl_node *prev = list->head;
        for (size_t i = 0; i < index - 1; i++) {
            prev = prev->next;
        }
        new_node->next = prev->next;
        prev->next = new_node;
    }

    list->size++;
}
SLItem sl_delete_at(SLList *list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return 0;
    }
    sl_node *target = NULL;

    if (index == 0) {
        target = list->head;
        list->head = target->next;
    } else {
        sl_node *prev = list->head;

        for (size_t i = 0; i < index - 1; i++) {
            prev = prev->next;
        }
        target = prev->next;
        prev->next = target->next;
    }
    SLItem data = target->data;
    free(target);
    list->size--;
    return data;
}
void sl_destroy(SLList *list)
{
    if (list == NULL) {
        return;
    }

    while (list->head) {
        sl_delete_at(list, 0);
    }
    free(list);
}
SLItem sl_get(SLList *list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return 0;
    }
    sl_node *target = list->head;

    for (size_t i = 0; i < index; i++) {
        target = target->next;
    }
    return target->data;
}
void sl_print(SLList *list)
{
    if (list == NULL || list->head == NULL) {
        return;
    }
    sl_node *current = list->head;

    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("\n");
}
size_t sl_size(SLList *list)
{
    return list ? list->size : 0;
}