#include "quick.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>

//This function is responsible for creating the partitions for the quick sort algorithm.
uint32_t partition(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    uint32_t i = low - 1;
    for (uint32_t j = low; j < high; j++) {
        if (cmp(stats, A[j - 1], A[high - 1]) < 0) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[high - 1]);
    return i + 1;
}

//This is the recursive function for the quick sort algorithm.
void quick_sorter(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    if (low < high) {
        uint32_t p = partition(stats, A, low, high);
        quick_sorter(stats, A, low, p - 1);
        quick_sorter(stats, A, p + 1, high);
    }
}

//This function calls the quick sort recursive function.
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}

