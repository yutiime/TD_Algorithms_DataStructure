#include <stdio.h> 
#include <time.h> 
#include "fib.h"

int main() {
    int n = 35; // value for test perf. 
    clock_t start, end;
    float time_used;
    int result;

    printf("Calcul du %dème nombre de Fibonacci\n\n", n);

    // naive function test
    printf("=== Algorithme Naif récursif ===\n");
    start = clock();
    result = nthFibonacci(n);
    end = clock();
    time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("Résultat: %d\n", result);
    printf("Temps d'exécution: %f secondes\n\n", time_used);

    // dynamic prog. function test 
    printf("=== Algorithme aveec Programmation Dynamiqeuu ===\n");
    start = clock();
    result = nthFibonacciDynamic(n);
    end = clock();
    time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
    printf("Résultat: %d\n", result);
    printf("Temps d'exécution: %f secondes\n\n", time_used);


    return 0;
}  