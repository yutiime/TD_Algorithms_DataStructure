#include <stdio.h>
#include "fib.h"

// Naive algorithm : 
// for calculating the nth terms 
int nthFibonacci(int n){
    // if n is 0 or 1 ---> return n
    if (n <= 1){
        return n;
    }
    // sum of two Fibonacci numbers
    return nthFibonacci(n - 1) + nthFibonacci(n - 2);
}


// dynamic algorithm : 
int nthFibonacciUtil(int n, int memo[]) { 

    // if n is 0 or 1 ---> return n 
    if (n<=1) { 
        return n; 
    }

    // checking th eresult in memo table 
    if (memo[n] != -1) { 
        return memo[n]; 
    }

    // caculating Fibonacci number and storing in memo 
    memo[n] = nthFibonacciUtil(n-1, memo) + nthFibonacciUtil(n-2, memo);
    return memo[n]; 
}   
    

int nthFibonacciDynamic(int n) { 

    //create a memoization table 
    int memo[n+1]; 
    for (int i = 0; i <= n; i++) { 
        memo[i] = -1; 
    } 
    return nthFibonacciUtil(n, memo); 
} 

