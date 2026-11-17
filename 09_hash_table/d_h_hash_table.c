#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    DH_INITIAL_CAPACITY = 11
};

typedef struct {
    int key;
} DHItem;

typedef enum {
    SLOT_EMPTY,
    SLOT_OCCUPIED,
    SLOT_DELETED
} DHState;

typedef struct {
    DHItem data;
    DHState state;
} DHSlot;

struct DoubleHashingHashTable {
    DHSlot* slots;
    size_t capacity;
    size_t size;
};
typedef struct DoubleHashingHashTable DHSet;

DHSet* dh_create(void)
{
    DHSet* table = calloc(1, sizeof(*table));
    if (table == NULL) {
        return NULL;
    }
    table->capacity = DH_INITIAL_CAPACITY;
    table->slots = calloc(table->capacity, sizeof(*table->slots));
    if (table->slots == NULL) {
        free(table);
        return NULL;
    }
    return table;
}
void dh_destroy(DHSet* table)
{
    if (table == NULL) {
        return;
    }
    free(table->slots);
    free(table);
}
static bool is_prime(size_t number)
{
    if (number < 2) {
        return false;
    }
    if (number % 2 == 0) {
        return number == 2;
    }
    for (size_t divisor = 3; divisor * divisor <= number; divisor += 2) {
        if (number % divisor == 0) {
            return false;
        }
    }
    return true;
}
static size_t normalize_key(int key, size_t capacity)
{
    int result = key % capacity;

    return result < 0 ? result + capacity : result;
}
static size_t hash1(int key, size_t capacity)
{
    return normalize_key(key, capacity);
}
static size_t hash2(int key, size_t capacity)
{
    return 1 + normalize_key(key, capacity - 1);
}
static size_t probe(int key, size_t i, size_t capacity)
{
    return (hash1(key, capacity) + i * hash2(key, capacity)) % capacity;
}
bool dh_search(DHSet* table, int key, size_t* index_out, DHItem* data_out)
{
    if (table == NULL) {
        return false;
    }
    size_t start = hash1(key, table->capacity);
    size_t step = hash2(key, table->capacity);

    for (size_t i = 0; i < table->capacity; i++) {
        size_t index = (start + i * step) % table->capacity;
        probe(key, i, table->capacity);
        DHSlot* target = &table->slots[index];

        if (target->state == SLOT_EMPTY) {
            return false;
        }
        if (target->state == SLOT_OCCUPIED && target->data.key == key) {

            if (index_out != NULL) {
                *index_out = index;
            }
            if (data_out != NULL) {
                *data_out = target->data;
            }
            return true;
        }
    }
    return false;
}
bool dh_insert(DHSet* table, DHItem data)
{
    if (table == NULL) {
        return false;
    }
    size_t index;
    if (dh_search(table, data.key, &index, NULL)) {
        table->slots[index].data = data;
        return false;
    }
    size_t start = hash1(data.key, table->capacity);
    size_t step = hash2(data.key, table->capacity);

    for (size_t i = 0; i < table->capacity; i++) {
        index = (start + i * step) % table->capacity;
        DHSlot* slot = &table->slots[index];

        if (slot->state != SLOT_OCCUPIED) {
            slot->data = data;
            slot->state = SLOT_OCCUPIED;
            table->size++;

            return true;
        }
    }
    return false;
}
int delete_key(DHSet* ht, int key)
{
    int index = dh_search(ht, key);

    if (index == -1) {
        return false;
    }

    ht->slots[index].state = SLOT_DELETED;
    ht->size--;

    return true;
}
void print_hash_table(DHSet* ht)
{
    printf("Hash Table\n");

    for (int i = 0; i < ht->capacity; i++) {
        printf("[%d] ", i);

        if (ht->slots[i].state == SLOT_EMPTY) {
            printf("EMPTY");
        } else if (ht->slots[i].state == SLOT_DELETED) {
            printf("DELETED");
        } else {
            printf("%d", ht->slots[i].key);
        }

        printf("\n");
    }

    printf("Size: %d / %d\n", ht->size, ht->capacity);
}

void free_hash_table(DHSet* ht)
{
    free(ht->slots);
    ht->slots = NULL;
    ht->capacity = 0;
    ht->size = 0;
}

// int main(void)
//{
//     DHSet ht;
//
//     if (!init_hash_table(&ht, 11)) {
//         printf("Hash table initialization failed.\n");
//         return 1;
//     }
//
//     int values[] = { 2, 3, 5, 7, 11, 13, 19, 23, 25, 29 };
//     int count = sizeof(values) / sizeof(values[0]);
//
//     for (int i = 0; i < count; i++) {
//         int index = insert(&ht, values[i]);
//
//         if (index != -1) {
//             printf("Inserted %d at index %d\n", values[i], index);
//         } else {
//             printf("Cannot insert %d\n", values[i]);
//         }
//     }
//
//     printf("\n");
//     print_hash_table(&ht);
//
//     int key = 23;
//     int index = search(&ht, key);
//
//     if (index != -1) {
//         printf("\nFound %d at index %d\n", key, index);
//     } else {
//         printf("\n%d not found\n", key);
//     }
//
//     key = 5;
//
//     if (delete_key(&ht, key)) {
//         printf("\nDeleted %d\n", key);
//     } else {
//         printf("\n%d not found\n", key);
//     }
//
//     printf("\n");
//     print_hash_table(&ht);
//
//     key = 31;
//     index = insert(&ht, key);
//
//     if (index != -1) {
//         printf("\nInserted %d at index %d\n", key, index);
//     } else {
//         printf("\nCannot insert %d\n", key);
//     }
//
//     printf("\n");
//     print_hash_table(&ht);
//
//     free_hash_table(&ht);
//
//     return 0;
// }
