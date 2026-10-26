#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef int CDLItem;
typedef struct CDLNode *CDLNodeHandle;
typedef struct CircularDoublyLinkedList CDLList;

CDLList *cdl_create(void);
void cdl_destroy(CDLList *list);
bool cdl_insert_before(CDLList *list, CDLNodeHandle node, int value);
bool cdl_delete(CDLList *list, CDLNodeHandle node, int *value);
bool cdl_get(CDLList *list, CDLNodeHandle node, int *value);
bool cdl_set(CDLList *list, CDLNodeHandle node, int value);
CDLNodeHandle cdl_find(CDLList *list, int value);
bool cdl_insert_at(CDLList *list, size_t index, int value);
bool cdl_delete_at(CDLList *list, size_t index, int *value);
bool cdl_get_at(CDLList *list, size_t index, int *value);
size_t cdl_size(CDLList *list);
void cdl_print(CDLList *list);

#endif
