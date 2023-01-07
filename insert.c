#include "insert.h"

#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
//Thi function is responsible for running the insertion sort algorithm.
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 1; i < n; i++) {
        uint32_t index = i;
        uint32_t memory = move(stats, A[i]);
        //This is where the comparisons and movements occurr for this sorting algorithm.
        while (index > 0 && cmp(stats, memory, A[index - 1]) < 0) {
            A[index] = move(stats, A[index - 1]);
            index -= 1;
        }
        A[index] = move(stats, memory);
    }
}
