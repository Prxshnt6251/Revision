/*
 * ═══════════════════════════════════════════════════════════════════
 *  mergeSort.cpp  —  Merge Sort  (Recursive, Top-Down)
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Divide the array in half, recursively sort each half, then merge
 *  the two sorted halves in linear time.
 *
 *  RECURRENCE
 *  ──────────
 *  T(n) = 2·T(n/2) + Θ(n)
 *
 *  MASTER'S THEOREM  (Case 2)
 *  ──────────────────────────
 *  a = 2,  b = 2,  f(n) = n
 *  log_b(a) = log_2(2) = 1
 *  f(n) = Θ(n^1)  →  Case 2: T(n) = Θ(n log n)
 *
 *  SPACE : O(n) auxiliary (merge buffer)
 *  STABLE: YES
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"

extern long long g_iterations;

static void merge(std::vector<int>& arr, int l, int m, int r) {
    std::vector<int> left (arr.begin() + l, arr.begin() + m + 1);
    std::vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < (int)left.size() && j < (int)right.size()) {
        ++g_iterations;
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else                      arr[k++] = right[j++];
    }
    while (i < (int)left.size())  { ++g_iterations; arr[k++] = left[i++];  }
    while (j < (int)right.size()) { ++g_iterations; arr[k++] = right[j++]; }
}

static void mergeSortHelper(std::vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSortHelper(arr, l, m);
    mergeSortHelper(arr, m + 1, r);
    merge(arr, l, m, r);
}

void mergeSort(std::vector<int>& arr) {
    if (!arr.empty())
        mergeSortHelper(arr, 0, (int)arr.size() - 1);
}
