#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef int DLItem;
typedef struct DLNode *DLIter;
typedef struct DoublyLinkedList DLList;

DLList *dl_create(void);
void dl_destroy(DLList *list);
void dl_insert_at(DLList *list, size_t index, int value);
DLItem dl_delete_at(DLList *list, size_t index);
DLItem dl_get(DLList *list, size_t index);
size_t dl_size(DLList *list);
void dl_print(DLList *list);

#endif
