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
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t index;

    if (binary_search(arr, size, 7, &index)) {
        printf("index: %zu\n", index);
    }
}
// 1
// #define MAX_ITEMS 100
//
// typedef struct {
//    double weight; // 물건의 무게
//    double value;  // 물건의 가치
//    double ratio;  // 단위 무게당 가치
//    int id;        // 물건 번호
//} Item;
//
// int main(void)
//{
//    Item items[MAX_ITEMS];
//    Item temp;
//    int n;
//    int i, j;
//    double capacity;
//    double totalValue = 0.0;
//
//    // 물건 개수와 배낭의 용량 입력
//    scanf("%d %lf", &n, &capacity);
//
//    if (n < 1 || n > MAX_ITEMS || capacity < 0) {
//        return 1;
//    }
//
//    // 각 물건의 무게와 가치 입력
//    for (i = 0; i < n; i++) {
//        scanf("%lf %lf", &items[i].weight, &items[i].value);
//
//        if (items[i].weight <= 0 || items[i].value < 0) {
//            return 1;
//        }
//
//        items[i].ratio = items[i].value / items[i].weight;
//        items[i].id = i + 1;
//    }
//
//    // 단위 무게당 가치가 높은 순서로 정렬
//    for (i = 0; i < n - 1; i++) {
//        for (j = i + 1; j < n; j++) {
//            if (items[i].ratio < items[j].ratio) {
//                temp = items[i];
//                items[i] = items[j];
//                items[j] = temp;
//            }
//        }
//    }
//
//    // 배낭에 물건 담기
//    for (i = 0; i < n; i++) {
//        if (capacity <= 0) {
//            break;
//        }
//
//        if (items[i].weight <= capacity) {
//            // 물건 전체를 담을 수 있는 경우
//            capacity -= items[i].weight;
//            totalValue += items[i].value;
//
//            printf("%d번 물건: 전체 담기\n", items[i].id);
//        } else {
//            // 물건의 일부만 담는 경우
//            double fraction = capacity / items[i].weight;
//
//            totalValue += items[i].value * fraction;
//
//            printf("%d번 물건: %.2f%% 담기\n", items[i].id, fraction * 100.0);
//
//            capacity = 0;
//        }
//    }
//
//    printf("최대 가치: %.2f\n", totalValue);
//
//    return 0;
//}
// 2
//// Function to compare two items based on value-to-weight ratio
// int compare(const void *a, const void *b)
//{
//     const float *itemA = (const float *)a;
//     const float *itemB = (const float *)b;
//
//     float ratioA = itemA[0] / itemA[1];
//     float ratioB = itemB[0] / itemB[1];
//
//     if (ratioA < ratioB)
//         return 1;
//     if (ratioA > ratioB)
//         return -1;
//
//     return 0;
// }
//
// float fractionalKnapsack(float val[], float wt[], int capacity, int n)
//{
//     // Create an array to store value and weight
//     float items[n][2];
//
//     for (int i = 0; i < n; i++) {
//         items[i][0] = val[i];
//         items[i][1] = wt[i];
//     }
//
//     // Sort items based on value-to-weight ratio
//     qsort(items, n, sizeof(items[0]), compare);
//
//     float res = 0.0;
//     float currentCapacity = capacity;
//
//     // Process items in sorted order
//     for (int i = 0; i < n; i++) {
//         // Take the complete item
//         if (items[i][1] <= currentCapacity) {
//             res += items[i][0];
//             currentCapacity -= items[i][1];
//         }
//         // Take a fraction of the item
//         else {
//             res += (items[i][0] / items[i][1]) * currentCapacity;
//             // Knapsack is full
//             break;
//         }
//     }
//
//     return res;
// }
//
// int main()
//{
//     float val[] = {60, 100, 120};
//     float wt[] = {10, 20, 30};
//     int capacity = 50;
//
//     int n = sizeof(val) / sizeof(val[0]);
//
//     printf("%.2f", fractionalKnapsack(val, wt, capacity, n));
//
//     return 0;
// }
void greedy_algorithm(void)
{
}
void dynamic_programming(void)
{
}
void backtracking(void)
{
}
int main(void)
{
    size_t paradigm_number = 0;

    switch (paradigm_number) {
    case 0: {
        divide_and_conquer();

        break;
    }
    case 1:
        greedy_algorithm();
        break;
    case 2:
        dynamic_programming();
        break;
    case 3:
        backtracking();
        break;
    }
    return 0;
}