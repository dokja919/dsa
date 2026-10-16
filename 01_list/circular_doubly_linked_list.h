#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef int CDLItem;
typedef struct CDLNode *CDLIter;
typedef struct CircularDoublyLinkedList CDLList;

CDLList *cdl_create(void);
void cdl_destroy(CDLList *list);
void cdl_insert_at(CDLList *list, size_t index, int value);
CDLItem cdl_delete_at(CDLList *list, size_t index);
CDLItem cdl_get(CDLList *list, size_t index);
size_t cdl_size(CDLList *list);
void cdl_print(CDLList *list);

#endif
