#include <stdio.h>
#include <time.h>


int countPrimesNaive(int N);
int countPrimesSieve(int n);

int main() {
    int N;
    printf("Enter N: ");
    scanf("%d", &N);
    
    // test naive algorithm
    clock_t start = clock();
    int count_naive = countPrimesNaive(N);
    clock_t end = clock();
    double time_naive = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\n=== Naive Algorithm ===\n");
    printf("Number of primes < %d: %d\n", N, count_naive);
    printf("Execution time: %.6f seconds\n", time_naive);
    
    // test efficient algorithm
    start = clock();
    int count_sieve = countPrimesSieve(N);
    end = clock();
    double time_sieve = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\n=== Optimal Algorithm ===\n");
    printf("Number of primes < %d: %d\n", N, count_sieve);
    printf("Execution time: %.6f seconds\n", time_sieve);
    
    // Performance comparison
    printf("\n=== Comparison ===\n");
    if (time_naive > 0 && time_sieve > 0) {
        printf("Optimal algorithm is %.2fx faster\n", time_naive / time_sieve);
    }
    
    // COMPLEXITY ANALYSIS DEMONSTRATION
    printf("\n=== COMPLEXITY ANALYSIS ===\n");
    printf("Question: Show that complexity is O(n log log n)\n\n");
    printf("PROOF:\n");
    printf("1. Multiples of each prime p <= sqrt(n)\n");
    printf("2. For a prime p, approximately n/p multiples are marked\n");
    printf("3. Total cost = n * sum(1/p) for prime p <= sqrt(n)\n");
    printf("4. Meissel-Mertens theorem:\n");
    printf("   sum(1/p) <= log(log(x)) + M (M = constant)\n");
    printf("5. With x = sqrt(n): sum(1/p) <= log(log(sqrt(n))) + M\n");
    printf("6. log(log(sqrt(n))) = log(log(n)/2) = log(log(n)) - log(2)\n");
    printf("7. Therefore: Cost = n * (log(log(n)) - log(2) + M)\n");
    printf("8. CONCLUSION: Complexity = O(n log log n)\n");
    printf("\nThis explains why the sieve is more efficient than naive O(n*sqrt(n))\n");
    
    return 0;
}
