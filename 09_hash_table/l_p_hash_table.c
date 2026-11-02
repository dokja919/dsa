#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    LP_INITIAL_CAPACITY = 8
};

typedef enum {
    EMPTY,
    OCCUPIED,
    DELETED
} LPState;

typedef struct {
    int key;
    int value;
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
    table->items = malloc(sizeof(*table->items) * table->capacity);
    if (table->items == NULL) {
        free(table);
        return NULL;
    }
    for (size_t i = 0; i < table->capacity; i++) {
        table->items[i].state = EMPTY;
    }
    table->size = 0;

    return table;
}
size_t lp_hash(int key)
{
    int remainder = key % LP_INITIAL_CAPACITY;

    if (remainder < 0) {
        remainder += LP_INITIAL_CAPACITY;
    }
    return (size_t)remainder;
}
bool lp_insert(LPSet *ht, int key, int value)
{
    size_t index = lp_hash(key);
    size_t first_deleted = LP_INITIAL_CAPACITY;

    for (int i = 0; i < LP_INITIAL_CAPACITY; i++) {
        size_t pos = (index + i) % LP_INITIAL_CAPACITY;
        LPItem *entry = &ht->items[pos];
        // 이미 존재하는 key라면 value 갱신
        if (entry->state == OCCUPIED && entry->key == key) {
            entry->value = value;
            return true;
        }
        // 삭제된 공간 기록
        if (entry->state == DELETED && first_deleted == LP_INITIAL_CAPACITY) {
            first_deleted = pos;
        }
        // 빈 공간 발견
        if (entry->state == EMPTY) {
            size_t target = (first_deleted != LP_INITIAL_CAPACITY)
                                ? first_deleted
                                : pos;

            ht->items[target].key = key;
            ht->items[target].value = value;
            ht->items[target].state = OCCUPIED;

            return true;
        }
    }
    // 빈 공간은 없지만 삭제된 공간이 있는 경우
    if (first_deleted != LP_INITIAL_CAPACITY) {
        ht->items[first_deleted].key = key;
        ht->items[first_deleted].value = value;
        ht->items[first_deleted].state = OCCUPIED;
        return true;
    }
    return false; // 테이블이 가득 참
}
bool lp_search(LPSet *ht, int key, int *value)
{
    size_t index = lp_hash(key);

    for (int i = 0; i < LP_INITIAL_CAPACITY; i++) {
        size_t pos = (index + i) % LP_INITIAL_CAPACITY;
        LPItem *entry = &ht->items[pos];

        if (entry->state == EMPTY) {
            return false;
        }
        if (entry->state == OCCUPIED && entry->key == key) {
            if (value != NULL) {
                *value = entry->value;
            }
            return true;
        }
    }
    return false;
}
bool lp_delete(LPSet *ht, int key)
{
    size_t index = lp_hash(key);

    for (int i = 0; i < LP_INITIAL_CAPACITY; i++) {
        size_t pos = (index + i) % LP_INITIAL_CAPACITY;
        LPItem *entry = &ht->items[pos];

        if (entry->state == EMPTY) {
            return false;
        }
        if (entry->state == OCCUPIED && entry->key == key) {
            entry->state = DELETED;
            return true;
        }
    }
    return false;
}
void lp_print(LPSet *ht)
{
    for (size_t i = 0; i < LP_INITIAL_CAPACITY; i++) {
        LPItem *entry = &ht->items[i];
        printf("[%d] ", i);

        if (entry->state == EMPTY) {
            printf("EMPTY\n");
        } else if (entry->state == DELETED) {
            printf("DELETED\n");
        } else {
            printf("key: %d, value: %d\n", entry->key, entry->value);
        }
    }
}
int main(void)
{
    LPSet *table = lp_create();

    lp_insert(table, 12, 100);
    lp_insert(table, 22, 200);
    lp_insert(table, 32, 300);

    printf("=== Hash Table ===\n");
    lp_print(table);

    int value;

    printf("\n=== Search ===\n");

    if (lp_search(table, 22, &value)) {
        printf("Found: key = 22, value = %d\n", value);
    } else {
        printf("Not found\n");
    }

    printf("\n=== Delete ===\n");
    lp_delete(table, 22);
    lp_print(table);

    return 0;
}
