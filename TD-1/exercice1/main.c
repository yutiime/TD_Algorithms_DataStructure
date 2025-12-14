#include <stdio.h> 
#include <time.h> 
#include "fib.h"

int main() {
    int n = 35; // value for test perf. 
    clock_t start, end;
    float time_used;
    int result;

    printf("Computing the %dth Fibonacci number\n\n", n);

    // naive function test
    printf("=== Naive Recursive Algorithm ===\n");
    start = clock();
    result = nthFibonacci(n);
    end = clock();
    time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("Result: %d\n", result);
    printf("Execution time: %f seconds\n\n", time_used);

    // dynamic programming function test
    printf("=== Algorithm with Dynamic Programming ===\n");
    start = clock();
    result = nthFibonacciDynamic(n);
    end = clock();
    time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("Result: %d\n", result);
    printf("Execution time: %f seconds\n\n", time_used);


    return 0;
}  