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
int fibonacci_topdown(size_t index, int sequence[])
{
    // if (index <= 1) {
    //     return n;
    // }
    // return fibonacci_topdown(index - 2) + fibonacci_topdown(index - 1);
    if (index == 0) {
        return 0;
    }
    if (index <= 2) {
        sequence[0] = 1;

        if (index == 2) {
            sequence[1] = 1;
        }
        return 1;
    }
    if (sequence[index - 1] != 0) {
        return sequence[index - 1];
    }
    sequence[index - 1] = fibonacci_topdown(index - 2, sequence) + fibonacci_topdown(index - 1, sequence);

    return sequence[index - 1];
}
bool fibonacci_tabulation(size_t index, int sequence[], int* value)
{
    if (value == NULL) {
        return false;
    }
    if (index == 0) {
        *value = 0;
        return true;
    }
    sequence[0] = 1;

    if (index >= 2) {
        sequence[1] = 1;
    }
    for (size_t i = 2; i < index; i++) {
        sequence[i] = sequence[i - 2] + sequence[i - 1];
    }
    *value = sequence[index - 1];

    return true;
}
bool fibonacci_optimized(size_t index, int* value)
{
    if (value == NULL) {
        return false;
    }
    if (index == 0) {
        *value = 0;
        return true;
    }
    int prev = 1;
    int current = 1;

    for (size_t i = 2; i < index; i++) {
        int next = prev + current;
        prev = current;
        current = next;
    }
    *value = current;

    return true;
}
void dynamic_programming(void)
{
    size_t index = 5;
    size_t fibonacci = 0;
    int value;

    switch (fibonacci) {
    case 0: {
        int* memo = calloc(index, sizeof(*memo));
        if (memo == NULL) {
            return;
        }
        value = fibonacci_topdown(index, memo);

        printf("%d\n", value);
        print_array(memo, index);
        free(memo);
        break;
    }
    case 1: {
        int* table = malloc(index * sizeof(*table));
        if (table == NULL) {
            return;
        }
        if (fibonacci_tabulation(index, table, &value)) {
            printf("%d\n", value);
            print_array(table, index);
        }
        free(table);
        break;
    }
    case 2:
        if (fibonacci_optimized(index, &value)) {
            printf("%d\n", value);
        }
        break;
    }
}
void backtracking(void)
{
}
int main(void)
{
    size_t paradigm = 2;

    switch (paradigm) {
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