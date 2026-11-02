#include <stdbool.h>
#include <stdio.h>

#define TABLE_SIZE 10

typedef enum {
    EMPTY,
    OCCUPIED,
    DELETED
} State;

typedef struct {
    int key;
    int value;
    State state;
} Entry;

typedef struct {
    Entry entries[TABLE_SIZE];
} HashTable;

// 해시 함수
size_t hash(int key)
{
    return (unsigned int)key % TABLE_SIZE;
}

// 초기화
void ht_init(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->entries[i].state = EMPTY;
    }
}

// 삽입
bool ht_insert(HashTable *ht, int key, int value)
{
    size_t index = hash(key);
    size_t first_deleted = TABLE_SIZE;

    for (int i = 0; i < TABLE_SIZE; i++) {
        size_t pos = (index + i) % TABLE_SIZE;
        Entry *entry = &ht->entries[pos];

        // 이미 존재하는 key라면 value 갱신
        if (entry->state == OCCUPIED && entry->key == key) {
            entry->value = value;
            return true;
        }

        // 삭제된 공간 기록
        if (entry->state == DELETED && first_deleted == TABLE_SIZE) {
            first_deleted = pos;
        }

        // 빈 공간 발견
        if (entry->state == EMPTY) {
            size_t target = (first_deleted != TABLE_SIZE)
                                ? first_deleted
                                : pos;

            ht->entries[target].key = key;
            ht->entries[target].value = value;
            ht->entries[target].state = OCCUPIED;

            return true;
        }
    }

    // 빈 공간은 없지만 삭제된 공간이 있는 경우
    if (first_deleted != TABLE_SIZE) {
        ht->entries[first_deleted].key = key;
        ht->entries[first_deleted].value = value;
        ht->entries[first_deleted].state = OCCUPIED;
        return true;
    }

    return false; // 테이블이 가득 참
}

// 탐색
bool ht_search(HashTable *ht, int key, int *value)
{
    size_t index = hash(key);

    for (int i = 0; i < TABLE_SIZE; i++) {
        size_t pos = (index + i) % TABLE_SIZE;
        Entry *entry = &ht->entries[pos];

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

// 삭제
bool ht_delete(HashTable *ht, int key)
{
    size_t index = hash(key);

    for (int i = 0; i < TABLE_SIZE; i++) {
        size_t pos = (index + i) % TABLE_SIZE;
        Entry *entry = &ht->entries[pos];

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

// 출력
void ht_display(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *entry = &ht->entries[i];

        printf("[%d] ", i);

        if (entry->state == EMPTY) {
            printf("EMPTY\n");
        } else if (entry->state == DELETED) {
            printf("DELETED\n");
        } else {
            printf("key: %d, value: %d\n",
                   entry->key, entry->value);
        }
    }
}

// 테스트
int main(void)
{
    HashTable ht;
    ht_init(&ht);

    ht_insert(&ht, 12, 100);
    ht_insert(&ht, 22, 200);
    ht_insert(&ht, 32, 300);

    printf("=== Hash Table ===\n");
    ht_display(&ht);

    int value;

    printf("\n=== Search ===\n");

    if (ht_search(&ht, 22, &value)) {
        printf("Found: key = 22, value = %d\n", value);
    } else {
        printf("Not found\n");
    }

    printf("\n=== Delete ===\n");
    ht_delete(&ht, 22);
    ht_display(&ht);

    return 0;
}
