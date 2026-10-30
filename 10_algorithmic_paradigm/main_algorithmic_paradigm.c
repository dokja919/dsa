#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
bool binary_search(int arr[], size_t n, int key, size_t *index)
{
    size_t i = 0;
    size_t j = n;

    while (i < j) {
        size_t mid = i + (j - i) / 2;

        if (arr[mid] == key) {
            *index = mid;
            return true;
        } else if (key < arr[mid]) {
            j = mid;
        } else {
            i = mid + 1;
        }
    }
    return false;
}
void divide_and_conquer(void)
{
    int arr[] = { 1, 3, 5, 7, 9, 11, 13 };
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t index;

    if (binary_search(arr, size, 7, &index)) {
        printf("index: %zu\n", index);
    }
}
typedef struct {
    int id;        // 물건 번호
    double weight; // 물건의 무게
    double value;  // 물건의 가치
} Item;

int main(void)
{
    Item items[] = {
        { 1, 10.0, 60.0 },
        { 2, 20.0, 100.0 },
        { 3, 30.0, 120.0 }
    };
    size_t n = sizeof(items) / sizeof(items[0]);
    double capacity = 50.0;
    double totalValue = 0.0;

    // 단위 무게당 가치가 높은 순서로 정렬
    for (size_t i = 0; i + 1 < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            double ratio_i = items[i].value / items[i].weight;
            double ratio_j = items[j].value / items[j].weight;

            if (ratio_i < ratio_j) {
                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
    for (size_t i = 0; i < n; i++) {

        if (capacity <= 0.0) {
            break;
        }

        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;

            printf("%d번 물건: 전체 담기\n", items[i].id);
        } else {
            double fraction = capacity / items[i].weight;

            totalValue += items[i].value * fraction;

            printf("%d번 물건: %.2f%% 담기\n", items[i].id, fraction * 100.0);

            capacity = 0.0;
        }
    }
    // for (size_t i = 0; i < n; i++) {
    //     if (capacity >= items[i].weight) {
    //         capacity -= items[i].weight;
    //         totalValue += items[i].value;
    //     } else {
    //         totalValue += (items[i].value / items[i].weight) * capacity;

    //        capacity = 0;
    //        break;
    //    }
    //}
    printf("최대 가치: %.2f\n", totalValue);

    return 0;
}
void greedy_algorithm(void)
{
}
void dynamic_programming(void)
{
}
void backtracking(void)
{
}
// int main(void)
//{
//     size_t paradigm_number = 0;
//
//     switch (paradigm_number) {
//     case 0: {
//         divide_and_conquer();
//
//         break;
//     }
//     case 1:
//         greedy_algorithm();
//         break;
//     case 2:
//         dynamic_programming();
//         break;
//     case 3:
//         backtracking();
//         break;
//     }
//     return 0;
// }