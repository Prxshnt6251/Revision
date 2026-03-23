/*
 * ═══════════════════════════════════════════════════════════════════
 *  radixSort.cpp  —  Radix Sort  (LSD, base 10)
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Sorts integers digit by digit from the Least Significant Digit
 *  (LSD) to the Most Significant Digit, using a stable counting sort
 *  as the subroutine at each digit position.
 *
 *  COMPLEXITY
 *  ──────────
 *  d = number of digits = O(log_{base}(maxVal))
 *  Each pass of counting sort: Θ(n + base)
 *  Total: T(n) = Θ(d · (n + base))
 *
 *  When base = Θ(n) and d = O(1):  T(n) = Θ(n)
 *  For fixed base-10 and d = log_{10}(maxVal):
 *    T(n) = Θ(n · log_{10}(maxVal))  ≈ Θ(n · d)
 *
 *  NOT a comparison sort → Master's Theorem does not apply.
 *
 *  SPACE : O(n + base) auxiliary
 *  STABLE: YES
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"

extern long long g_iterations;

static void countSortByDigit(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n);
    int count[10] = {};

    for (int i = 0; i < n; ++i) { ++g_iterations; count[(arr[i] / exp) % 10]++; }
    for (int i = 1; i < 10; ++i) count[i] += count[i-1];
    for (int i = n-1; i >= 0; --i) {
        ++g_iterations;
        output[--count[(arr[i] / exp) % 10]] = arr[i];
    }
    arr = output;
}

void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    // Works for non-negative integers; shift if negatives present
    int minVal = *std::min_element(arr.begin(), arr.end());
    if (minVal < 0)
        for (auto& x : arr) x -= minVal;   // shift to non-negative

    int maxVal = *std::max_element(arr.begin(), arr.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countSortByDigit(arr, exp);

    if (minVal < 0)
        for (auto& x : arr) x += minVal;   // shift back
}
