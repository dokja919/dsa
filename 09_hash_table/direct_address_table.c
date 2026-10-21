
#include <stdio.h>

#define SIZE 100

int table[SIZE];
int used[SIZE] = {0};

// 삽입
void insert(int key, int value)
{
    if (key < 0 || key >= SIZE) {
        printf("잘못된 키입니다.\n");
        return;
    }

    table[key] = value;
    used[key] = 1;
}

// 탐색
int search(int key)
{
    if (key < 0 || key >= SIZE || !used[key]) {
        return -1;
    }

    return table[key];
}

// 삭제
void delete(int key)
{
    if (key >= 0 && key < SIZE) {
        used[key] = 0;
    }
}

int main(void)
{
    insert(10, 100);
    insert(25, 500);
    insert(7, 300);

    printf("key 10: %d\n", search(10));
    printf("key 25: %d\n", search(25));
    printf("key 15: %d\n", search(15));

    delete(10);
    printf("삭제 후 key 10: %d\n", search(10));

    return 0;
}

// #include <stdio.h>
//
// #define U 10 // 사용할 수 있는 키: 0 ~ 9
//
// typedef struct {
//     int key;
//     const char *value;
// } Item;
//
// Item *T[U]; // Direct Address Table
//
//// Direct-Address-Search(T, k)
// Item *direct_address_search(Item *T[], int k)
//{
//     if (k < 0 || k >= U)
//         return NULL;
//
//     return T[k];
// }
//
//// Direct-Address-Insert(T, x)
// void direct_address_insert(Item *T[], Item *x)
//{
//     if (x->key < 0 || x->key >= U)
//         return;
//
//     T[x->key] = x;
// }
//
//// Direct-Address-Delete(T, x)
// void direct_address_delete(Item *T[], Item *x)
//{
//     if (x->key < 0 || x->key >= U)
//         return;
//
//     T[x->key] = NULL;
// }
//
// int main(void)
//{
//     // 테이블 초기화: 모든 칸을 NIL(NULL)로 설정
//     for (int i = 0; i < U; i++)
//         T[i] = NULL;
//
//     Item a = {3, "Apple"};
//     Item b = {7, "Banana"};
//
//     // 삽입
//     direct_address_insert(T, &a);
//     direct_address_insert(T, &b);
//
//     // 탐색
//     Item *result = direct_address_search(T, 3);
//
//     if (result != NULL)
//         printf("탐색 결과: key = %d, value = %s\n", result->key, result->value);
//     else
//         printf("데이터가 없습니다.\n");
//
//     // 삭제
//     direct_address_delete(T, &a);
//
//     // 삭제 여부 확인
//     result = direct_address_search(T, 3);
//
//     if (result != NULL)
//         printf("탐색 결과: %s\n", result->value);
//     else
//         printf("key 3의 데이터가 삭제되었습니다.\n");
//
//     return 0;
// }