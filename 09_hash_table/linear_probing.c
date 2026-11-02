#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int *linear_probing(const int arr[], size_t n, size_t m)
{
    if (m == 0 || (n > 0 && arr == NULL) ||
        m > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *hash_table = malloc(m * sizeof(*hash_table));

    if (hash_table == NULL) {
        return NULL;
    }

    // Initialize hash table
    for (size_t i = 0; i < m; ++i) {
        hash_table[i] = -1;
    }

    // Insert elements using linear probing
    for (size_t i = 0; i < n; ++i) {
        int value = arr[i];
        size_t index;

        if (value >= 0) {
            index = (size_t)value % m;
        } else {
            size_t magnitude = (size_t)(-(long long)value);
            size_t remainder = magnitude % m;
            index = (remainder == 0) ? 0 : m - remainder;
        }

        for (size_t count = 0; count < m; ++count) {
            size_t pos = (count >= m - index)
                             ? count - (m - index)
                             : index + count;

            if (hash_table[pos] == value) {
                break;
            }

            if (hash_table[pos] == -1) {
                hash_table[pos] = value;
                break;
            }
        }
    }

    return hash_table;
}

// Driver code
int main(void)
{
    int arr[] = { 4, 14, 24, 44 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t m = 10;

    int *result = linear_probing(arr, n, m);

    if (result == NULL) {
        fprintf(stderr, "Failed to create the hash table.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < m; ++i) {
        printf("%d ", result[i]);
    }

    putchar('\n');

    free(result);

    return EXIT_SUCCESS;
}
