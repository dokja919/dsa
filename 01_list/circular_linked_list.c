#include "circular_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct CLNode {
    CLItem data;
    struct CLNode* next;
} CLNode;

struct CircularLinkedList {
    CLNode* tail;
    size_t size;
};

CLList* cl_create(void)
{
    CLList* list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    list->size = 0;
    list->tail = NULL;

    return list;
}
static CLNode* node_create(int value)
{
    CLNode* new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}
void cl_insert_at(CLList* list, size_t index, int value)
{
    if (list == NULL || index > list->size) {
        return;
    }
    CLNode* new_node = node_create(value);
    if (new_node == NULL) {
        return;
    }
    if (list->tail == NULL) {
        new_node->next = new_node;
        list->tail = new_node;
    } else {
        CLNode* prev = list->tail;

        for (size_t i = 0; i < index; i++) {
            prev = prev->next;
        }
        new_node->next = prev->next;
        prev->next = new_node;

        if (prev == list->tail) {
            list->tail = new_node;
        }
    }
    list->size++;
}
CLItem cl_delete_at(CLList* list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return 0;
    }
    CLNode* prev = list->tail;

    for (size_t i = 0; i < index; i++) {
        prev = prev->next;
    }
    CLNode* target = prev->next;

    if (prev == target) {
        list->tail = NULL;
    } else {
        prev->next = target->next;

        if (list->tail == target) {
            list->tail = prev;
        }
    }
    CLItem data = target->data;
    free(target);
    list->size--;
    return data;
}
void cl_destroy(CLList* list)
{
    if (list == NULL) {
        return;
    }

    while (list->tail) {
        cl_delete_at(list, 0);
    }
    free(list);
}
CLItem cl_get(CLList* list, size_t index)
{
    if (list == NULL || index >= list->size) {
        return 0;
    }

    if (index == list->size - 1) {
        return list->tail->data;
    }

    CLNode* target = list->tail->next;
    for (size_t i = 0; i < index; i++) {
        target = target->next;
    }
    return target->data;
}
void cl_print(CLList* list)
{
    if (list == NULL || list->tail == NULL) {
        return;
    }
    CLNode* current = list->tail->next;

    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != list->tail->next);

    printf("head\n");
}
size_t cl_size(CLList* list)
{
    return list ? list->size : 0;
}