#include "heap.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
//This function is responsible for determinig the max_child for the heap algorithm.
uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= last && cmp(stats, A[right - 1], A[left - 1]) > 0) {
        return right;
    }
    return left;
}

//This function is responsible for fixing the heap for the heap algorithm.
void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);
    while (mother <= last / 2 && !(found)) {
        if (cmp(stats, A[mother - 1], A[great - 1]) < 0) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}

//This function is responsible for building the heap for the heap algorithm.
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t i = last / 2; i > (first - 1); i--) {
        fix_heap(stats, A, i, last);
    }
}

//This function is responsible for running the heap sorting algorithm.
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last);
    for (uint32_t i = last; i > first; i--) {
        swap(stats, &A[first - 1], &A[i - 1]);
        fix_heap(stats, A, first, i - 1);
    }
}
