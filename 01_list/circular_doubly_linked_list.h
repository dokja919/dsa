#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef int CDLItem;
typedef struct CDLNode *CDLNodeHandle;
typedef struct CircularDoublyLinkedList CDLList;

CDLList *cdl_create(void);
void cdl_destroy(CDLList *list);
bool cdl_insert_before(CDLList *list, CDLNodeHandle node, CDLItem data);
bool cdl_delete(CDLList *list, CDLNodeHandle node, CDLItem *data);
bool cdl_get(CDLList *list, CDLNodeHandle node, CDLItem *data);
bool cdl_set(CDLList *list, CDLNodeHandle node, CDLItem data);
CDLNodeHandle cdl_find(CDLList *list, CDLItem data);
bool cdl_insert_at(CDLList *list, size_t index, CDLItem data);
bool cdl_delete_at(CDLList *list, size_t index, CDLItem *data);
bool cdl_get_at(CDLList *list, size_t index, CDLItem *data);
size_t cdl_size(CDLList *list);
void cdl_print(CDLList *list);

#endif
