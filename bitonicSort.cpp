/*
 * ═══════════════════════════════════════════════════════════════════
 *  bitonicSort.cpp  —  Bitonic Sort
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  A parallel comparison-based sorting algorithm that first produces
 *  a bitonic sequence (one that first increases then decreases), then
 *  merges it into a sorted sequence.  Works on arrays whose size is
 *  a power of 2 (padded with INT_MAX otherwise).
 *
 *  RECURRENCE  (Akra-Bazzi method)
 *  ───────────────────────────────
 *  bitonicMerge  : T_m(n) = 2·T_m(n/2) + Θ(n)
 *    → Akra-Bazzi: p=1  →  T_m(n) = Θ(n log n)
 *  bitonicSort   : T_s(n) = 2·T_s(n/2) + T_m(n)
 *                         = 2·T_s(n/2) + Θ(n log n)
 *
 *  AKRA-BAZZI for T_s:
 *  g(n) = n log n,  a=2,  b=2  →  p=1
 *  ∫_1^n g(u)/u^2 du = ∫_1^n (log u)/u du = (log n)²/2
 *  T_s(n) = Θ(n · (log n)²)
 *
 *  Sequential time complexity: Θ(n log²n)
 *  Parallel time complexity  : Θ(log²n)   ← its real strength
 *
 *  SPACE : O(log²n) stack
 *  STABLE: NO
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"
#include <climits>

extern long long g_iterations;

static void compAndSwap(std::vector<int>& arr, int i, int j, bool ascending) {
    ++g_iterations;
    if ((arr[i] > arr[j]) == ascending)
        std::swap(arr[i], arr[j]);
}

static void bitonicMerge(std::vector<int>& arr, int lo, int cnt, bool ascending) {
    if (cnt <= 1) return;
    int k = cnt / 2;
    for (int i = lo; i < lo + k; ++i)
        compAndSwap(arr, i, i + k, ascending);
    bitonicMerge(arr, lo,     k, ascending);
    bitonicMerge(arr, lo + k, k, ascending);
}

static void bitonicSortHelper(std::vector<int>& arr, int lo, int cnt, bool ascending) {
    if (cnt <= 1) return;
    int k = cnt / 2;
    bitonicSortHelper(arr, lo,     k, true);    // sort first half ascending
    bitonicSortHelper(arr, lo + k, k, false);   // sort second half descending
    bitonicMerge(arr, lo, cnt, ascending);
}

void bitonicSort(std::vector<int>& arr) {
    // Pad to next power of 2
    int n    = arr.size();
    int padN = 1;
    while (padN < n) padN <<= 1;
    arr.resize(padN, INT_MAX);
    bitonicSortHelper(arr, 0, padN, true);
    arr.resize(n);  // remove padding
}
