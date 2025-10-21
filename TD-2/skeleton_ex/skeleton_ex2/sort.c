#include <stdlib.h>
#include "sort.h"
#include "utils.h"

void selection_sort(int *arr, int n)
 {
    // selection sort iterative
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap_int(&arr[min_index], &arr[i]);
        }
    }
}

void insertion_sort(int *arr, int n)
{
    // insertion sort iterative

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void bubble_sort(int *arr, int n)
{
    // bubble sort iterative
    // bubble sort iterative
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // simple swap using helper
                swap_int(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void merge(int *arr, int *tmp, int l, int m, int r)
{
    // merge function

    int i = l , j = m, k = l; 
    while (i < m && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }
    // copy remaining left part
    while (i < m) {
        tmp[k++] = arr[i++];
    }
    // copy remaining right part
    while (j <= r) {
        tmp[k++] = arr[j++];
    }
}

void mergesort_rec(int *arr, int *tmp, int l, int r)
{
    // recursive steps of merge sort
    if (l < r) { 
        int m = l + (r - l) / 2; 
        mergesort_rec(arr, tmp, l, m); 
        mergesort_rec(arr, tmp, m + 1, r); 
        merge(arr, tmp, l, m + 1, r); 
        // copy tmp to arr
        for (int i = l; i <= r; i++) { 
            arr[i] = tmp[i]; 
        }
    }
}

void merge_sort(int *arr, int n)
{
    if (!arr || n <= 1)
        return;
    int *tmp = (int *)malloc((size_t)n * sizeof(int));
    if (!tmp)
        return;
    mergesort_rec(arr, tmp, 0, n - 1);
    free(tmp);
}
int partition(int *arr, int l, int r)
{
    // partition function
    int pivot = arr[r]; 
    int i = l - 1;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // swap arr[i] and arr[j]
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    // place pivot at correct position
    int tmp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = tmp;
    return i + 1;
}

void quick_sort_rec(int *arr, int l, int r)
{
    // recursive steps of quick sort
    if (l < r) { 
        int pi = partition(arr, l, r); 
        quick_sort_rec(arr, l, pi - 1); 
        quick_sort_rec(arr, pi + 1, r); 
    }
}

void quick_sort(int *arr, int n)
{
    if (!arr || n <= 1)
        return;
    quick_sort_rec(arr, 0, n - 1);
    
}