/*
 * ═══════════════════════════════════════════════════════════════════
 *  binaryInsertionSort.cpp  —  Binary Insertion Sort
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Insertion sort, but uses RECURSIVE BINARY SEARCH to find the
 *  correct insertion position in the sorted prefix, reducing the
 *  number of key comparisons.
 *
 *  BINARY SEARCH RECURRENCE  (Master's Theorem)
 *  ─────────────────────────────────────────────
 *  T_search(n) = T(n/2) + O(1)
 *  a = 1,  b = 2,  f(n) = 1
 *  log_b(a) = log_2(1) = 0
 *  f(n) = Θ(n^0) → Case 2:  T_search(n) = Θ(log n)
 *
 *  FULL SORT COMPLEXITY
 *  ─────────────────────
 *  Comparisons: O(n log n)   (n elements × O(log n) binary search)
 *  Shifts      : O(n²)       (still need to move elements)
 *  Overall     : O(n²)       (dominated by shifts)
 *
 *  SPACE : O(log n) stack for recursion, O(1) auxiliary otherwise
 *  STABLE: YES
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"

extern long long g_iterations;

// Recursive binary search: returns insertion position in arr[lo..hi]
static int binarySearchPos(const std::vector<int>& arr, int key, int lo, int hi) {
    if (lo >= hi) {
        ++g_iterations;
        return (key < arr[lo]) ? lo : lo + 1;
    }
    int mid = lo + (hi - lo) / 2;
    ++g_iterations;
    if (key == arr[mid])  return mid + 1;
    if (key  < arr[mid])  return binarySearchPos(arr, key, lo, mid - 1);
    else                  return binarySearchPos(arr, key, mid + 1, hi);
}

void binaryInsertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int pos = binarySearchPos(arr, key, 0, i - 1);
        // Shift elements right to make room
        for (int j = i; j > pos; --j) {
            ++g_iterations;
            arr[j] = arr[j-1];
        }
        arr[pos] = key;
    }
}
