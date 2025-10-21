#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"
#include "utils.h"

int main(void)
{
    int n = 10000; // taille du tableau
    int *orig = (int*)malloc(n * sizeof(int));
    if (!orig) return 1;

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) orig[i] = rand() % (n * 10);

    int *tmp = (int*)malloc(n * sizeof(int));
    if (!tmp) { free(orig); return 1; }

    clock_t start, end;
    double spent;

    // selection sort
    copy_array(orig, tmp, n);
    start = clock();
    selection_sort(tmp, n);
    end = clock();
    spent = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("selection_sort: %.6f seconds\n", spent);

    // insertion sort
    copy_array(orig, tmp, n);
    start = clock();
    insertion_sort(tmp, n);
    end = clock();
    spent = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("insertion_sort: %.6f seconds\n", spent);

    // bubble sort
    copy_array(orig, tmp, n);
    start = clock();
    bubble_sort(tmp, n);
    end = clock();
    spent = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("bubble_sort: %.6f seconds\n", spent);

    // merge sort
    copy_array(orig, tmp, n);
    start = clock();
    merge_sort(tmp, n);
    end = clock();
    spent = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("merge_sort: %.6f seconds\n", spent);

    // quick sort
    copy_array(orig, tmp, n);
    start = clock();
    quick_sort(tmp, n);
    end = clock();
    spent = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("quick_sort: %.6f seconds\n", spent);

    free(orig);
    free(tmp);
    return 0;
}
