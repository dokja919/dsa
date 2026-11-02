#include <stdio.h>

enum { LP_CAPACITY = 16 };

size_t hash(int key)
{
    int remainder = key % LP_CAPACITY;

    if (remainder < 0) {
        remainder += LP_CAPACITY;
    }
    return (size_t)remainder;
}
int probe(int H[], int key)
{
    int index = hash(key);
    int i = 0;
    while (H[(index + i) % LP_CAPACITY] != 0)
        i++;
    return (index + i) % LP_CAPACITY;
}
void Insert(int H[], int key)
{
    int index = hash(key);
    if (H[index] != 0)
        index = probe(H, key);
    H[index] = key;
}
int Search(int H[], int key)
{
    int index = hash(key);
    int i = 0;
    while (H[(index + i) % LP_CAPACITY] != key)
        i++;
    return (index + i) % LP_CAPACITY;
}
int main()
{
    int HT[10] = { 0 };
    Insert(HT, 12);
    Insert(HT, 25);
    Insert(HT, 35);
    Insert(HT, 26);
    printf("\nKey found at %d\n", Search(HT, 35));
    return 0;
}