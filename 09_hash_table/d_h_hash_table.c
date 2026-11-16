#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SLOT_EMPTY,
    SLOT_OCCUPIED,
    SLOT_DELETED
} SlotState;

typedef struct {
    int key;
    SlotState state;
} HashSlot;

typedef struct {
    HashSlot* table;
    size_t capacity;
    size_t size;
} HashTable;

static bool is_prime(int n)
{
    if (n < 2) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return true;
}
static int normalize_key(int key, int mod)
{
    int result = key % mod;
    return result < 0 ? result + mod : result;
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

bool init_hash_table(HashTable* table, size_t capacity)
{
    if (capacity < 3 || !is_prime(capacity)) {
        return false;
    }

    table->table = malloc(sizeof(HashSlot) * capacity);
    if (table->table == NULL) {
        return false;
    }

    table->capacity = capacity;
    table->size = 0;

    for (int i = 0; i < capacity; i++) {
        table->table[i].key = 0;
        table->table[i].state = SLOT_EMPTY;
    }

    return true;
}
int search(HashTable* ht, int key)
{
    for (int i = 0; i < ht->capacity; i++) {
        int index = probe(key, i, ht->capacity);

        if (ht->table[index].state == SLOT_EMPTY) {
            return -1;
        }

        if (ht->table[index].state == SLOT_OCCUPIED &&
            ht->table[index].key == key) {
            return index;
        }
    }

    return -1;
}

int insert(HashTable* ht, int key)
{
    if (search(ht, key) != -1) {
        return -1;
    }

    int first_deleted = -1;

    for (int i = 0; i < ht->capacity; i++) {
        int index = probe(key, i, ht->capacity);

        if (ht->table[index].state == SLOT_DELETED) {
            if (first_deleted == -1) {
                first_deleted = index;
            }
        } else if (ht->table[index].state == SLOT_EMPTY) {
            int insert_index = first_deleted != -1 ? first_deleted : index;

            ht->table[insert_index].key = key;
            ht->table[insert_index].state = SLOT_OCCUPIED;
            ht->size++;

            return insert_index;
        }
    }

    if (first_deleted != -1) {
        ht->table[first_deleted].key = key;
        ht->table[first_deleted].state = SLOT_OCCUPIED;
        ht->size++;

        return first_deleted;
    }

    return -1;
}

int delete_key(HashTable* ht, int key)
{
    int index = search(ht, key);

    if (index == -1) {
        return false;
    }

    ht->table[index].state = SLOT_DELETED;
    ht->size--;

    return true;
}

void print_hash_table(HashTable* ht)
{
    printf("Hash Table\n");

    for (int i = 0; i < ht->capacity; i++) {
        printf("[%d] ", i);

        if (ht->table[i].state == SLOT_EMPTY) {
            printf("EMPTY");
        } else if (ht->table[i].state == SLOT_DELETED) {
            printf("DELETED");
        } else {
            printf("%d", ht->table[i].key);
        }

        printf("\n");
    }

    printf("Size: %d / %d\n", ht->size, ht->capacity);
}

void free_hash_table(HashTable* ht)
{
    free(ht->table);
    ht->table = NULL;
    ht->capacity = 0;
    ht->size = 0;
}

// int main(void)
//{
//     HashTable ht;
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
