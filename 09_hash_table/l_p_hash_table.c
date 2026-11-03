#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    LP_INITIAL_CAPACITY = 8 // 16
};

typedef enum {
    EMPTY,
    OCCUPIED,
    DELETED
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
bool lp_insert(LPSet *table, LPItem data)
{
    if (table == NULL) {
        return false;
    }
    size_t start = lp_hash(table, data.key);
    size_t first_deleted = table->capacity;

    for (size_t i = 0; i < table->capacity; i++) {
        size_t index = (start + i) % table->capacity;
        LPItem *item = &table->items[index];

        if (item->state == OCCUPIED && item->key == data.key) {
            return true;
        }
        if (item->state == DELETED && first_deleted == table->capacity) {
            first_deleted = index;
        }
        if (item->state == EMPTY) {
            size_t empty = (first_deleted != table->capacity)
                               ? first_deleted
                               : index;
            table->items[empty] = data;
            table->items[empty].state = OCCUPIED;

            return true;
        }
    }
    // 빈 공간은 없지만 삭제된 공간이 있는 경우
    if (first_deleted != table->capacity) {
        table->items[first_deleted] = data;
        table->items[first_deleted].state = OCCUPIED;
        return true;
    }
    return false; // 테이블이 가득 참
}
bool lp_search(LPSet *table, int key, LPItem *data)
{
    if (table == NULL) {
        return false;
    }
    size_t start = lp_hash(table, key);

    for (size_t i = 0; i < table->capacity; i++) {
        size_t pos = (start + i) % table->capacity;
        LPItem *target = &table->items[pos];

        if (target->state == EMPTY) {
            return false;
        }
        if (target->state == OCCUPIED && target->key == key) {
            if (data != NULL) {
                data = target;
            }
            return true;
        }
    }
    return false;
}
bool lp_delete(LPSet *table, int key, LPItem *data)
{
    size_t start = lp_hash(table, key);

    for (size_t i = 0; i < table->capacity; i++) {
        size_t index = (start + i) % table->capacity;
        LPItem *target = &table->items[index];

        if (target->state == EMPTY) {
            return false;
        }
        if (target->state == OCCUPIED && target->key == key) {
            target->state = DELETED;
            data = target;
            return true;
        }
    }
    return false;
}
void lp_print(LPSet *table)
{
    for (size_t i = 0; i < table->capacity; i++) {
        LPItem *current = &table->items[i];
        printf("[%d] ", i);

        if (current->state == EMPTY) {
            printf("EMPTY\n");
        } else if (current->state == DELETED) {
            printf("DELETED\n");
        } else {
            printf("key: %d\n", current->key);
        }
    }
}
int main(void)
{
    LPSet *table = lp_create();

    lp_insert(table, (LPItem){ 12, EMPTY });
    lp_insert(table, (LPItem){ 22, EMPTY });
    lp_insert(table, (LPItem){ 32, EMPTY });

    printf("=== Hash Table ===\n");
    lp_print(table);

    LPItem data;

    printf("\n=== Search ===\n");

    if (lp_search(table, 22, &data)) {
        printf("Found: key = 22\n", data.key);
    } else {
        printf("Not found\n");
    }

    printf("\n=== Delete ===\n");
    lp_delete(table, 22, &data);
    lp_print(table);

    return 0;
}
