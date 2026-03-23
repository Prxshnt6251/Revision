/*
 * ═══════════════════════════════════════════════════════════════════
 *  selectionSort.cpp  —  Selection Sort
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Divides the list into a sorted prefix and an unsorted suffix.
 *  On each pass, finds the minimum of the unsorted portion and
 *  appends it to the sorted prefix.
 *
 *  RECURRENCE
 *  ──────────
 *  T(n) = T(n-1) + (n-1)   →   Θ(n²)  always (no early exit)
 *  (same arithmetic-series argument as Bubble Sort)
 *
 *  SPACE : O(1) auxiliary
 *  STABLE: NO  (swap may skip equal elements)
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"

extern long long g_iterations;

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            ++g_iterations;
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            std::swap(arr[i], arr[minIdx]);
    }
}
