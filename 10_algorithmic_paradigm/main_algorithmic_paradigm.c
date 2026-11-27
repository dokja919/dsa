#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(int* array, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
bool binary_search(int arr[], size_t n, int key, size_t* index)
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
    int array[] = { 1, 3, 5, 7, 9, 11, 13 };
    size_t n = sizeof(array) / sizeof(array[0]);
    int key = 7;
    size_t index;

    if (binary_search(array, n, key, &index)) {
        printf("index: %zu\n", index);
    }
}
typedef struct {
    int id;
    double weight;
    double value;
    double ratio;
} Item;

bool fractional_knapsack(Item items[], size_t n, double capacity, double* max_value)
{
    if (items == NULL || capacity < 0.0 || max_value == NULL) {
        return false;
    }
    *max_value = 0.0;

    for (size_t i = 0; i < n; i++) {
        if (items[i].weight <= 0.0 || items[i].value < 0.0) {
            return false;
        }
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
    for (size_t i = 0; i < n && capacity > 0.0; i++) {
        const double fraction = (items[i].weight <= capacity)
                                    ? 1.0
                                    : capacity / items[i].weight;
        double obtained_value = items[i].value * fraction;

        *max_value += obtained_value;
        capacity -= items[i].weight * fraction;

        printf("item %d: value = %.2f, selected = %.2f%%, obtained value = %.2f\n",
               items[i].id, items[i].value, fraction * 100.0, obtained_value);
    }
    return true;
}
void greedy_algorithm(void)
{
    Item items[] = {
        { 1, 10.0, 60.0, 0.0 },
        { 2, 20.0, 100.0, 0.0 },
        { 3, 30.0, 120.0, 0.0 },
        { 4, 5.0, 50.0, 0.0 },
        { 5, 15.0, 45.0, 0.0 }
    };
    size_t n = sizeof(items) / sizeof(items[0]);
    double capacity = 50.0;
    double max_value;

    if (fractional_knapsack(items, n, capacity, &max_value)) {
        printf("max value: %.2f\n", max_value);
    }
}
int fibonacci_topdown(size_t n, int* memo)
{
    // if (n <= 1) {
    //     return n;
    // }
    // return fibonacci_topdown(n - 2) + fibonacci_topdown(n - 1);
    if (n <= 1) {
        memo[0] = 0;
        if (n == 1) {
            memo[1] = 1;
        }
        return (int)n;
    }
    if (memo[n] != -1) {
        return memo[n];
    }
    memo[n] = fibonacci_topdown(n - 2, memo) + fibonacci_topdown(n - 1, memo);

    return memo[n];
}
bool fibonacci_tabulation(size_t n, int table[], int* value)
{
    if (value == NULL) {
        return false;
    }
    table[0] = 0;
    if (n >= 1) {
        table[1] = 1;
    }
    for (size_t i = 2; i < n + 1; i++) {
        table[i] = table[i - 2] + table[i - 1];
    }
    *value = table[n];

    return true;
}
bool fibonacci_iterative(size_t n, int* value)
{
    if (value == NULL) {
        return false;
    }
    int prev = 0;
    int current = 1;

    for (size_t i = 2; i <= n; i++) {
        int next = prev + current;
        prev = current;
        current = next;
    }
    *value = (n == 0) ? prev : current;

    return true;
}
void dynamic_programming(void)
{
    size_t n = 0;
    size_t method = 0;
    int value;

    switch (method) {
    case 0: {
        int* memo = malloc((n + 1) * sizeof(*memo));
        if (memo == NULL) {
            return;
        }
        for (size_t i = 0; i < n + 1; i++) {
            memo[i] = -1;
        }
        value = fibonacci_topdown(n, memo);

        printf("%d\n", value);
        print_array(memo, n + 1);
        free(memo);

        break;
    }
    case 1: {
        int* table = malloc((n + 1), sizeof(*table));
        if (table == NULL) {
            return;
        }
        if (fibonacci_tabulation(n, table, &value)) {
            printf("%d\n", value);
            print_array(table, n + 1);
        }
        free(table);
        break;
    }
    case 2:
        if (fibonacci_iterative(n, &value)) {
            printf("%u", value);
        }
        break;
    }
}
void backtracking(void)
{
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