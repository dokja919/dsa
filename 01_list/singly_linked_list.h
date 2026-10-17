#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stddef.h>

typedef int SLItem;
typedef struct SinglyLinkedList SLList;

SLList *sl_create(void);
void sl_destroy(SLList *list);
void sl_insert_at(SLList *list, size_t index, int value);
SLItem sl_delete_at(SLList *list, size_t index);
SLItem sl_get(SLList *list, size_t index);
void sl_print(SLList *list);
size_t sl_size(SLList *list);

#endif
