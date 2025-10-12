#include <stdio.h>
#include <time.h>


int countPrimesNaive(int N);
int countPrimesSieve(int n);

int main() {
    int N;
    printf("Entrer N: ");
    scanf("%d", &N);
    
    // tst algorithme naif
    clock_t start = clock();
    int count_naive = countPrimesNaive(N);
    clock_t end = clock();
    double time_naive = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\n=== Algorithme Naïf ===\n");
    printf("Nombre de nombres premiers < %d: %d\n", N, count_naive);
    printf("Temps d'exécution: %.6f secondes\n", time_naive);
    
    // test efficient algo
    start = clock();
    int count_sieve = countPrimesSieve(N);
    end = clock();
    double time_sieve = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\n=== Algorithm Optimal ===\n");
    printf("Nombre de nombres premiers < %d: %d\n", N, count_sieve);
    printf("Temps d'exécution: %.6f secondes\n", time_sieve);
    
    // Comparaison des performances
    printf("\n=== Comparaison ===\n");
    if (time_naive > 0 && time_sieve > 0) {
        printf("L'algo optimal est %.2fx plus rapide\n", time_naive / time_sieve);
    }
    
    // DEMONSTRATION DE COMPLEXITE
    printf("\n=== ANALYSE DE COMPLEXITE ===\n");
    printf("Question: Montrer que la complexite est O(n log log n)\n\n");
    printf("DEMONSTRATION:\n");
    printf("1. Les multiples de chaque premier p <= sqrt(n)\n");
    printf("2. Pour un premier p, on marque environ n/p multiples\n");
    printf("3. Cout total = n * somme(1/p) pour p premier <= sqrt(n)\n");
    printf("4. Theoreme de Meissel-Mertens:\n");
    printf("   somme(1/p) <= log(log(x)) + M (M = constante)\n");
    printf("5. Avec x = sqrt(n): somme(1/p) <= log(log(sqrt(n))) + M\n");
    printf("6. log(log(sqrt(n))) = log(log(n)/2) = log(log(n)) - log(2)\n");
    printf("7. Donc: Cout = n * (log(log(n)) - log(2) + M)\n");
    printf("8. CONCLUSION: Complexite = O(n log log n)\n");
    printf("\nCeci explique pourquoi l'algo est plus efficace que l'algo naif O(n*sqrt(n))\n");
    
    return 0;
}
