#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool binary_search(int arr[], size_t n, int key, size_t *index)
{
    if (arr == NULL || index == NULL) {
        return false;
    }
    size_t low = 0;
    size_t high = n;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] == key) {
            *index = mid;
            return true;
        }
        if (key < arr[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return false;
}
void divide_and_conquer(void)
{
    int arr[] = { 1, 3, 5, 7, 9, 11, 13 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int key = 7;
    size_t index;

    if (binary_search(arr, n, key, &index)) {
        printf("index: %zu\n", index);
    }
}
typedef struct {
    int id;
    double weight;
    double value;
    double ratio;
} Item;

bool fractional_knapsack(Item items[], size_t n, double capacity, double *max_value)
{
    if (items == NULL || capacity < 0.0 || max_value == NULL) {
        return false;
    }
    for (size_t i = 0; i < n; i++) {
        items[i].ratio = items[i].value / items[i].weight;
    }
    for (size_t i = 1; i < n; i++) {
        Item key = items[i];
        size_t j = i;

        while (j > 0 && items[j - 1].ratio < key.ratio) {
            items[j] = items[j - 1];
            j--;
        }
        items[j] = key;
    }
    for (size_t i = 0; i < n; i++) {

        if (capacity <= 0.0) {
            break;
        }
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            *max_value += items[i].value;
            printf("item of %d\n", items[i].id);
        } else {
            double fraction = capacity / items[i].weight;
            printf("%.2f%% of item of %d\n", fraction * 100.0, items[i].id);
            capacity = 0.0;
            *max_value += items[i].value * fraction;
        }
    }
    return true;
}
void greedy_algorithm(void)
{
    Item items[] = {
        { 1, 10.0, 60.0, 0.0 },
        { 2, 20.0, 100.0, 0.0 },
        { 3, 30.0, 120.0, 0.0 }
    };
    size_t n = sizeof(items) / sizeof(items[0]);
    double capacity = 50.0;
    double max_value = 0.0;

    if (fractional_knapsack(items, n, capacity, &max_value)) {
        printf("max value: %.2f\n", max_value);
    }
}
void dynamic_programming(void)
{
}
void backtracking(void)
{
}
void print_array(int array[], size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main(void)
{
    size_t paradigm_number = 1;

    switch (paradigm_number) {
    case 0:
        divide_and_conquer();
        break;
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