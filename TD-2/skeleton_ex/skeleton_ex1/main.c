#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "search.h"
#include "utils.h"

int main(void)
{
    int n = 10;
    int target = 5;
    
    // dynamic allocation
    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation error\n");
        return 1;
    }
    

    // sorted array
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    
    printf("Array: [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n-1) printf(", ");
    }
    printf("]\n");
    
    printf("Searching for: %d\n", target);
    printf("Sorted: %s\n\n", is_sorted_nondecreasing(arr, n) ? "Yes" : "No");
    

    // variables to measure time
    clock_t start, end;
    double cpu_time_used;
    int result;
    

    // test linear search with time
    start = clock();
    result = linear_search(arr, n, target);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Linear Search: %d (time: %.6f seconds)\n", result, cpu_time_used);
    

    // test jump search with time
    start = clock();
    result = jump_search(arr, n, target);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Jump Search: %d (time: %.6f seconds)\n", result, cpu_time_used);
    

    // test binary search with time
    start = clock();
    result = binary_search(arr, n, target);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Binary Search: %d (time: %.6f seconds)\n", result, cpu_time_used);
    

    // test with unsorted array
    printf("\n--- Unsorted Array ---\n");
    arr[0] = 9; arr[1] = 3; arr[2] = 5; // mix
    
    printf("Sorted: %s\n", is_sorted_nondecreasing(arr, n) ? "Yes" : "No");
    printf("Jump Search: %d (should be -1)\n", jump_search(arr, n, target));
    printf("Binary Search: %d (should be -1)\n", binary_search(arr, n, target));
    
    free(arr);
    return 0;
}
