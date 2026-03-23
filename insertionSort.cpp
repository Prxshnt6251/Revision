/*
 * ═══════════════════════════════════════════════════════════════════
 *  insertionSort.cpp  —  Insertion Sort
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Builds the sorted array one element at a time by inserting each
 *  new element into its correct position within the already-sorted
 *  prefix.
 *
 *  RECURRENCE
 *  ──────────
 *  Worst (reverse sorted) : T(n) = T(n-1) + (n-1)  →  Θ(n²)
 *  Best  (already sorted) : T(n) = T(n-1) + 1       →  Θ(n)
 *  Average                :                            Θ(n²)
 *
 *  (Linear recurrence, not amenable to Master's Theorem directly;
 *   solved by telescoping / arithmetic series.)
 *
 *  SPACE : O(1) auxiliary
 *  STABLE: YES
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"

extern long long g_iterations;

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j   = i - 1;
        while (j >= 0 && arr[j] > key) {
            ++g_iterations;
            arr[j + 1] = arr[j];
            --j;
        }
        ++g_iterations;  // last failed comparison
        arr[j + 1] = key;
    }
}
