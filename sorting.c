#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "haeisqn:p:r:"
//This is the array that is implemented to iterate through the sorting options.
typedef enum { INSERTION, HEAP, SHELL, QUICK } Sorts;
//This is the array that is implemented to iterate through the sorting names.
const char *names[] = { "Insertion Sort", "Heap Sort", "Shell Sort", "Quick Sort" };
//This is the array that is implemented to iterate through the sorting functions
void (*sorts[])() = { insertion_sort, heap_sort, shell_sort, quick_sort };
//This section of code is the main and is responmsible for the operating the command line options.
int main(int argc, char **argv) {
    Set s = empty_set(); //The set is responsible for
    //Initializes the stats structure and variable for stat colecting from the sorts
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;

    int opt = 0;
    int seed = 13371453;
    int size = 100;
    int elements = 100;

    bool default_statement = true;
    //Command line section of the code.
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        //This if statement is responsible for determining if an input is faulty.
        if (opt == '?') {
            printf(
                "SYNOPSIS\n    A collection of comparison-based sorting algorithms.\n\nUSAGE\n    "
                "./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n   -h   "
                "           display program help and usage.\n   -a              enable all "
                "sorts.\n   -e              enable Heap Sort.\n   -i              enable Insertion "
                "Sort.\n   -s              enable Shell Sort.\n   -q              enable Quick "
                "Sort.\n   -n length       specify number of array elements (default: 100).\n   -p "
                "elements     specify number of elements to print (default: 100).\n   -r seed      "
                "   specify random seed (default: 13371453).\n");
            return -1;
        }
        //This section of is responsible for processing the user's valid input.
        switch (opt) {
        case 'n': size = atoi(optarg); break;
        case 'p': elements = atoi(optarg); break;
        case 'r': seed = atoi(optarg); break;
        case 'a':
            s = insert_set(HEAP, s);
            s = insert_set(INSERTION, s);
            s = insert_set(SHELL, s);
            s = insert_set(QUICK, s);
            default_statement = false;
            break;
        case 'e':
            s = insert_set(HEAP, s);
            default_statement = false;
            break;
        case 'i':
            s = insert_set(INSERTION, s);
            default_statement = false;
            break;
        case 's':
            s = insert_set(SHELL, s);
            default_statement = false;
            break;
        case 'q':
            s = insert_set(QUICK, s);
            default_statement = false;
            break;
        case 'h': return 1;
        }
    }
    //Next two lines of code are responsible for setting the radnom seed and creating the dynamically allocated array for the sort functions.
    srand(seed);
    uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));

    //This section of code is responsible for running the sorts and printing their results. Runs the sort functions based on the user's input.
    for (Sorts i = INSERTION; i <= QUICK; i++) {
        if (member_set(i, s)) {
            for (int i = 0; i < size; i++) {
                A[i] = random() & 0x3fffffff;
            }
            reset(&stats);
            (*sorts[i])(&stats, A, size);
            printf("%s, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares", names[i],
                size, stats.moves, stats.compares);
            if (elements > size) {
                elements = size;
            }
            for (int i = 0; i < elements; i++) {
                if (i % 5 == 0) {
                    printf("\n");
                }
                printf("%13" PRIu32, A[i]);
            }
            printf("\n");
        }
    }

    //This is the default statement that prints if the user does not input something or inputs a geopt argument incorrectly.
    if (default_statement) {
        printf(
            "Select at least one sort to perform.\nSYNOPSIS\n    A collection of comparison-based "
            "sorting algorithms.\n\nUSAGE\n    ./sorting [-haeisqn:p:r:] [-n length] [-p elements] "
            "[-r seed]\n\nOPTIONS\n   -h              display program help and usage.\n   -a       "
            "       enable all sorts.\n   -e              enable Heap Sort.\n   -i              "
            "enable Insertion Sort.\n   -s              enable Shell Sort.\n   -q              "
            "enable Quick Sort.\n   -n length       specify number of array elements (default: "
            "100).\n   -p elements     specify number of elements to print (default: 100).\n   -r "
            "seed         specify random seed (default: 13371453).\n");
    }
    free(A);
    return 0;
}
