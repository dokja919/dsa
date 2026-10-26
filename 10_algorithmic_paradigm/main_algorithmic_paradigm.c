#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int buffer[], size_t left, size_t mid, size_t right)
{
    size_t index = left;
    size_t a = left;
    size_t b = mid;

    while (a < mid && b < right) {
        if (array[a] <= array[b]) {
            buffer[index++] = array[a++];
        } else {
            buffer[index++] = array[b++];
        }
    }
    while (a < mid) {
        buffer[index++] = array[a++];
    }
    while (b < right) {
        buffer[index++] = array[b++];
    }
    for (size_t i = left; i < right; i++) {
        array[i] = buffer[i];
    }
}
void merge_sort(int array[], int buffer[], size_t left, size_t right)
{
    if (array == NULL || buffer == NULL || right <= left || right - left <= 1) {
        return;
    }
    size_t mid = left + (right - left) / 2;

    merge_sort(array, buffer, left, mid);
    merge_sort(array, buffer, mid, right);
    merge(array, buffer, left, mid, right);
}
void print_array(int array[], size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
bool divide_and_conquer(int array[], size_t n)
{
    if (array == NULL) {
        return false;
    }
    if (n <= 1) {
        print_array(array, n);
        return true;
    }
    int *buffer = malloc(sizeof(*buffer) * n);
    if (buffer == NULL) {
        return false;
    }
    merge_sort(array, buffer, 0, n);
    print_array(array, n);
    free(buffer);

    return true;
}
void greedy_algorithm(void)
{
}

/* 동적 프로그래밍 구현 위치: 상태, 점화식, 초기값 등을 정한 뒤 코드를 추가하세요. */
void dynamic_programming(void)
{
}

/* 백트래킹 구현 위치: 탐색 상태와 종료 조건 등을 정한 뒤 코드를 추가하세요. */
void backtracking(void)
{
}
int main(void)
{
    size_t sort_number = 0;

    switch (sort_number) {
    case 0: {
        int data[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};
        size_t n = sizeof(data) / sizeof(*data);
        if (divide_and_conquer(data, n) == false) {
            return 1;
        }
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