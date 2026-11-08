#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef int CDLItem;
typedef struct CDLNode* CDLIter;
typedef struct CircularDoublyLinkedList CDLList;

CDLList* cdl_create(void);
void cdl_destroy(CDLList* list);
bool cdl_insert_before(CDLList* list, CDLIter iter, CDLItem data);
bool cdl_search(CDLList* list, int value, CDLIter* iter_out, CDLItem* data_out);
bool cdl_delete_iter(CDLList* list, CDLIter iter, CDLItem* data_out);
bool cdl_set(CDLIter iter, CDLItem data);
bool cdl_insert_at(CDLList* list, size_t index, CDLItem data);
bool cdl_delete_at(CDLList* list, size_t index, CDLItem* data_out);
bool cdl_get_at(CDLList* list, size_t index, CDLItem* data_out);
size_t cdl_size(CDLList* list);
void cdl_print(CDLList* list);

#endif
