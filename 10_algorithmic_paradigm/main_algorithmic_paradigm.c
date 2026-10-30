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