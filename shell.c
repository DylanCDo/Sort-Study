#include "shell.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>

//This function is responsible for calculating the gaps for the shell sorting algorithm.
uint32_t gap(uint32_t x) {
    return (pow(3, x) - 1) / 2;
}

//This function is responsible for running the shell sorting algorithm.
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t x = (log(3 + (2 * n)) / log(3)); x > 0; x--) {
        for (uint32_t i = gap(x); i < n; i++) {
            uint32_t j = i;
            uint32_t memory = move(stats, A[i]);
            while (j >= x && cmp(stats, memory, A[j - x]) < 0) {
                A[j] = move(stats, A[j - x]);
                j -= x;
            }
            A[j] = move(stats, memory);
        }
    }
}
