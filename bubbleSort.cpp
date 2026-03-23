/*
 * ═══════════════════════════════════════════════════════════════════
 *  bubbleSort.cpp  —  Bubble Sort
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Repeatedly step through the list, compare adjacent elements and
 *  swap if they are in the wrong order. The pass is repeated until
 *  no swaps are needed.
 *
 *  RECURRENCE  (comparison count)
 *  ───────────────────────────────
 *  Worst / Average :  T(n) = T(n-1) + (n-1)   →  O(n²)
 *  Best (sorted)   :  T(n) = O(n)   (with early-exit flag)
 *
 *  MASTER'S THEOREM does NOT directly apply (not divide-and-conquer).
 *  We use the arithmetic-series argument instead:
 *    Total comparisons = (n-1) + (n-2) + … + 1 = n(n-1)/2  →  Θ(n²)
 *
 *  SPACE : O(1) auxiliary
 *  STABLE: YES
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"

extern long long g_iterations;

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            ++g_iterations;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;   // already sorted — best-case O(n)
    }
}
