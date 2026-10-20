#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}
// Bubble sort
void bubble_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }
    for (size_t pass = 0; pass < n - 1; pass++) {
        bool swapped = false;

        for (size_t i = 0; i < n - 1 - pass; i++) {
            if (array[i] > array[i + 1]) {
                swap(&array[i], &array[i + 1]);
                swapped = true;
            }
        }
        if (swapped == false) {
            break;
        }
    }
}
// Selection sort
void selection_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_index = i;

        for (size_t j = i + 1; j < n; j++) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(&array[i], &array[min_index]);
        }
    }
}
// Insertion sort
void insertion_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }
    for (size_t i = 1; i < n; i++) {
        int key = array[i];
        size_t position = i;

        while (position > 0 && key < array[position - 1]) {
            array[position] = array[position - 1];
            position--;
        }

        array[position] = key;
    }
}
// Merge sort
void merge(int array[], size_t begin, size_t middle, size_t end)
{
    size_t size = end - begin;
    int *buffer = malloc(size * sizeof(*buffer));
    if (buffer == NULL) {
        return;
    }

    size_t left = begin;
    size_t right = middle;

    size_t buffer_index = 0;
    while (left < middle && right < end) {
        if (array[left] <= array[right]) {
            buffer[buffer_index++] = array[left++];
        } else {
            buffer[buffer_index++] = array[right++];
        }
    }
    while (left < middle) {
        buffer[buffer_index++] = array[left++];
    }
    while (right < end) {
        buffer[buffer_index++] = array[right++];
    }

    for (size_t i = 0; i < size; i++) {
        array[begin + i] = buffer[i];
    }
    free(buffer);
}
void merge_sort(int array[], size_t begin, size_t end)
{
    if (array == NULL || end - begin < 2) {
        return;
    }
    size_t middle = (begin + end) / 2;

    merge_sort(array, begin, middle);
    merge_sort(array, middle, end);
    merge(array, begin, middle, end);
}
// Quick sort
size_t partition(int array[], size_t begin, size_t end)
{
    int pivot_value = array[begin];

    size_t left = begin;
    size_t right = end;
    do {
        do {
            left++;
        } while (left < end - 1 && array[left] < pivot_value);

        do {
            right--;
        } while (right >= left && array[right] > pivot_value);

        if (left >= right) {
            break;
        }
        swap(&array[left], &array[right]);

    } while (left < right);

    swap(&array[begin], &array[right]);

    return right;
}
void quick_sort(int array[], size_t begin, size_t end)
{
    if (array == NULL || end - begin < 2) {
        return;
    }
    size_t pivot_index = partition(array, begin, end);

    quick_sort(array, begin, pivot_index);
    quick_sort(array, pivot_index + 1, end);
}
// Heap sort
void heapify(int array[], size_t n, size_t root)
{
    size_t left_child = 2 * root + 1;
    if (left_child >= n) {
        return;
    }

    size_t right_child = left_child + 1;
    size_t larger_child = left_child;

    if (right_child < n && array[right_child] > array[left_child]) {
        larger_child = right_child;
    }

    if (array[root] >= array[larger_child]) {
        return;
    }
    swap(&array[root], &array[larger_child]);
    heapify(array, n, larger_child);
}
void heap_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }
    for (size_t i = n / 2; i > 0; i--) {
        heapify(array, n, i - 1);
    }
    for (size_t end = n - 1; end > 0; end--) {
        swap(&array[0], &array[end]);
        heapify(array, end, 0);
    }
}
// Counting sort
bool get_nonnegative_max(int array[], size_t n, size_t *max_value)
{
    if (array == NULL || n == 0 || max_value == NULL) {
        return false;
    }

    int temp = 0;

    for (size_t i = 0; i < n; i++) {
        if (array[i] < 0) {
            return false;
        }
        int value = array[i];

        if (value > temp) {
            temp = value;
        }
    }

    *max_value = (size_t)temp;
    return true;
}
void counting_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }

    size_t max_value;
    if (!get_nonnegative_max(array, n, &max_value)) {
        return;
    }

    size_t *counts = calloc(max_value + 1, sizeof(*counts));
    int *output = malloc(n * sizeof(*output));
    if (counts == NULL || output == NULL) {
        free(counts);
        free(output);
        return;
    }

    for (size_t i = 0; i < n; i++) {
        size_t value = (size_t)array[i];
        counts[value]++;
    }

    for (size_t value = 1; value <= max_value; value++) {
        counts[value] += counts[value - 1];
    }

    for (size_t i = n; i > 0; i--) {
        int value = array[i - 1];
        size_t counts_index = (size_t)value;

        size_t index = --counts[counts_index];
        output[index] = value;
    }
    for (size_t i = 0; i < n; i++) {
        array[i] = output[i];
    }

    free(counts);
    free(output);
}
// Radix sort
void counting_pass(int array[], size_t n, size_t place_value)
{
    size_t counts[10] = {0};

    int *output = malloc(n * sizeof(*output));
    if (output == NULL) {
        return;
    }

    for (size_t i = 0; i < n; i++) {
        size_t digit = ((size_t)array[i] / place_value) % 10;
        counts[digit]++;
    }

    for (size_t digit = 1; digit <= 9; digit++) {
        counts[digit] += counts[digit - 1];
    }

    for (size_t i = n; i > 0; i--) {
        int value = array[i - 1];
        size_t digit = ((size_t)value / place_value) % 10;

        size_t index = --counts[digit];
        output[index] = value;
    }
    for (size_t i = 0; i < n; i++) {
        array[i] = output[i];
    }

    free(output);
}
void radix_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }
    size_t max_value;
    if (!get_nonnegative_max(array, n, &max_value)) {
        return;
    }

    for (size_t place_value = 1; max_value / place_value > 0; place_value *= 10) {
        counting_pass(array, n, place_value);
    }
}
// Bucket sort
typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Bucket;
bool bucket_push(Bucket *bucket, int value)
{
    if (bucket->size >= bucket->capacity) {

        size_t new_capacity = (bucket->capacity == 0) ? 1 : bucket->capacity * 2;
        int *new_data = realloc(bucket->data, new_capacity * sizeof(*new_data));

        if (new_data == NULL) {
            return false;
        }
        bucket->data = new_data;
        bucket->capacity = new_capacity;
    }
    bucket->data[bucket->size++] = value;
    return true;
}
void bucket_sort(int array[], size_t n)
{
    if (array == NULL || n < 2) {
        return;
    }
    size_t max_value;
    if (!get_nonnegative_max(array, n, &max_value)) {
        return;
    }
    if (max_value == 0) {
        return;
    }
    Bucket *buckets = calloc(n, sizeof(*buckets));
    if (buckets == NULL) {
        return;
    }
    for (size_t i = 0; i < n; i++) {

        size_t bucket_index = (size_t)array[i] * (n - 1) / max_value;

        if (bucket_push(&buckets[bucket_index], array[i]) == false) {
            for (size_t j = 0; j < n; j++) {
                free(buckets[j].data);
            }

            free(buckets);
            return;
        }
    }
    for (size_t i = 0; i < n; i++) {
        insertion_sort(buckets[i].data, buckets[i].size);
    }

    size_t index = 0;

    for (size_t i = 0; i < n; i++) {

        for (size_t j = 0; j < buckets[i].size; j++) {

            array[index++] = buckets[i].data[j];
        }
        free(buckets[i].data);
    }

    free(buckets);
}

void print_array(int array[], size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main()
{
    int values[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3};
    // int values[] = {3, 3};
    size_t n = sizeof(values) / sizeof(*values);

    size_t sort_number = 8;

    switch (sort_number) {
    case 0:
        bubble_sort(values, n);
        break;
    case 1:
        selection_sort(values, n);
        break;
    case 2:
        insertion_sort(values, n);
        break;
    case 3:
        merge_sort(values, 0, n);
        break;
    case 4:
        quick_sort(values, 0, n);
        break;
    case 5:
        heap_sort(values, n);
        break;
    case 6:
        counting_sort(values, n);
        break;
    case 7:
        radix_sort(values, n);
        break;
    case 8:
        bucket_sort(values, n);
        break;
    default:
        printf("Invalid sort choice.\n");
        return 1;
    }
    print_array(values, n);

    return 0;
}
