/*
 * ═══════════════════════════════════════════════════════════════════
 *  quickSort.cpp  —  Quick Sort  (Randomised Pivot)
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Choose a pivot (randomised), partition the array so all elements
 *  less than the pivot are to its left and greater are to its right,
 *  then recursively sort both partitions.
 *
 *  RECURRENCE
 *  ──────────
 *  Worst  (always bad pivot): T(n) = T(n-1) + T(0)  + Θ(n) → O(n²)
 *  Best / Average (balanced):
 *    T(n) = 2·T(n/2) + Θ(n)
 *
 *  MASTER'S THEOREM  (Case 2) — average case
 *  ──────────────────────────────────────────
 *  a = 2,  b = 2,  f(n) = n
 *  log_b(a) = 1,  f(n) = Θ(n^1)  →  T(n) = Θ(n log n)
 *
 *  Randomisation makes worst case extremely unlikely (expected Θ(n log n)).
 *
 *  SPACE : O(log n) stack (average), O(n) worst
 *  STABLE: NO
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"
#include <cstdlib>

extern long long g_iterations;

static int partition(std::vector<int>& arr, int low, int high) {
    // Randomised pivot — swap random element with high
    int randIdx = low + rand() % (high - low + 1);
    std::swap(arr[randIdx], arr[high]);

    int pivot = arr[high];
    int i     = low - 1;
    for (int j = low; j < high; ++j) {
        ++g_iterations;
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

static void quickSortHelper(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low,    pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(std::vector<int>& arr) {
    srand(42);
    if (!arr.empty())
        quickSortHelper(arr, 0, (int)arr.size() - 1);
}
