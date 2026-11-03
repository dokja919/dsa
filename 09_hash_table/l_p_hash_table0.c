#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    LP_INITIAL_CAPACITY = 8
};

typedef enum {
    LP_EMPTY,
    LP_OCCUPIED,
    LP_DELETED
} LPState;

typedef struct {
    int key;
    LPState state;
} LPItem;

typedef struct {
    LPItem *items;
    size_t capacity;
    size_t size;
} LPSet;

LPSet *lp_create(void)
{
    LPSet *table = malloc(sizeof(*table));
    if (table == NULL) {
        return NULL;
    }
    table->capacity = LP_INITIAL_CAPACITY;
    table->size = 0;
    table->items = calloc(table->capacity, sizeof(*table->items));
    if (table->items == NULL) {
        free(table);
        return NULL;
    }
    return table;
}
void lp_destroy(LPSet *table)
{
    if (table != NULL) {
        free(table->items);
        free(table);
    }
}
size_t lp_hash(LPSet *table, int key)
{
    int capacity = (int)table->capacity;
    int remainder = key % capacity;

    if (remainder < 0) {
        remainder += capacity;
    }
    return (size_t)remainder;
}
bool insert(LPSet *table, int key)
{
    if (table == NULL) {
        return false;
    }
    size_t start = lp_hash(table, key);
    size_t first_deleted = table->capacity;

    for (size_t i = 0; i < table->capacity; i++) {
        size_t index = (start + i) % table->capacity;
        LPItem *item = &table->items[index];

        if (item->state == LP_OCCUPIED) {
            if (item->key == key) {
                return false; // 이미 존재하는 키는 중복 삽입하지 않는다.
            }
        } else if (item->state == LP_DELETED) {
            if (first_deleted == table->capacity) {
                first_deleted = index;
            }
        } else { // LP_EMPTY
            if (first_deleted != table->capacity) {
                index = first_deleted;
            }
            table->items[index].key = key;
            table->items[index].state = LP_OCCUPIED;
            table->size++;
            return false;
        }
    }
    if (first_deleted != table->capacity) {
        table->items[first_deleted].key = key;
        table->items[first_deleted].state = LP_OCCUPIED;
        table->size++;
        return true;
    }
    return false;
}
bool lp_search(LPSet *table, int key, LPItem *data)
{
    if (table == NULL) {
        return false;
    }
    size_t start = lp_hash(table, key);

    for (size_t i = 0; i < table->capacity; i++) {
        size_t index = (start + i) % table->capacity;
        LPItem *item = &table->items[index];

        if (item->state == LP_EMPTY) {
            return false;
        }
        if (item->state == LP_OCCUPIED && item->key == key) {
            *data = *item;
            return true;
        }
    }
    return false;
}
int delete(LPSet *table, int key)
{
    int index = lp_search(table, key);

    if (index == -1) {
        return 0; // 삭제할 키가 없다.
    }

    table->items[index].state = LP_DELETED;
    table->size--;
    return 1; // 삭제 성공
}

int main(void)
{
    LPSet *table = lp_create();
    if (table == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
        return 1;
    }

    insert(table, 12);
    insert(table, 20);
    insert(table, 28);
    insert(table, 35);

    printf("Key 28 found at %d\n", lp_search(table, 28));

    if (delete(table, 20)) {
        printf("Key 20 deleted.\n");
    }

    // 20을 삭제해도 tombstone 덕분에 뒤에 있던 28을 찾을 수 있다.
    printf("Key 28 found at %d\n", lp_search(table, 28));
    printf("Key 20 found at %d\n", lp_search(table, 20));

    lp_destroy(table);
    return 0;
}
