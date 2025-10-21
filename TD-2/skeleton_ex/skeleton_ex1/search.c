#include <math.h>
#include <stdio.h>
#include "search.h"
#include "utils.h"

int linear_search(int *arr, int n, int target)
{
    // linear search, return index of target
    // return -1 if not found
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int jump_search(int *arr, int n, int target)
{
    // jump search on sorted array, return index
    // of target, return -1 if not found
    if (!is_sorted_nondecreasing(arr, n)) {
        return -1;
    }
    
    int step = (int)sqrt(n);
    int prev = 0;

    // find block wehre element is prsent 
    while (arr[min_int(step, n) - 1] < target) {
        prev = step;
        step += (int)sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }

    // linear search in found block 
    while (arr[prev] < target) {
        prev++;
        if (prev == min_int(step, n)) {
            return -1;
        }
    }

    // check if element is foudnd 
    if (arr[prev] == target) {
        return prev;
    }

    return -1;
}

int binary_search(int *arr, int n, int target)
{
    // binary search on sorted array, return index
    // of target, return -1 if not found
    if (!is_sorted_nondecreasing(arr, n)) {
        return -1;
    }
    
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}