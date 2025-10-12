#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// naive algorithm to count prime numbers less than N
int countPrimesNaive(int N) {
    int count = 0;
    
    for (int x = 2; x < N; x++) {
        bool is_prime = true;
        for (int i = 2; i <= sqrt(x); i++) {
            if (x % i == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            count++;
        }
    }
    
    return count;
}

// efficient algorithm using eratosthenes
int countPrimesSieve(int n) {
    if (n <= 2) return 0;
    
    // create an array A of size n+1 initialized to true
    bool *A = malloc((n + 1) * sizeof(bool));
    if (!A) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    for (int i = 0; i <= n; i++)
        A[i] = true;

    // 0 and 1 are not primes
    A[0] = false;
    A[1] = false;

    // main sieve logic
    for (int i = 2; i <= sqrt(n); i++) {
        if (A[i]) {
            int j = i * i;
            while (j <= n) {
                A[j] = false;
                j += i;
            }
        }
    }

    // count primes smaller than n
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (A[i])
            count++;
    }

    free(A);
    return count;
}