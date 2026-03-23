/*
 * ═══════════════════════════════════════════════════════════════════
 *  countingSort.cpp  —  Counting Sort
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Non-comparison sort. Count occurrences of each distinct value,
 *  compute prefix sums, then write elements to their sorted positions.
 *  Works only for integer data with a bounded range [0, k].
 *
 *  COMPLEXITY
 *  ──────────
 *  T(n, k) = Θ(n + k)
 *    — Θ(k) to zero/fill count array
 *    — Θ(n) to count elements
 *    — Θ(k) prefix sums
 *    — Θ(n) to write output
 *  When k = O(n):  T(n) = Θ(n)  — beats comparison-sort lower bound!
 *
 *  NOT a comparison sort → Master's / Akra-Bazzi do not apply.
 *  Lower bound argument: avoids Ω(n log n) barrier because it
 *  exploits integer structure.
 *
 *  SPACE : O(n + k) auxiliary
 *  STABLE: YES
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"

extern long long g_iterations;

void countingSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *std::max_element(arr.begin(), arr.end());
    int minVal = *std::min_element(arr.begin(), arr.end());
    int range  = maxVal - minVal + 1;

    std::vector<int> count(range, 0);
    std::vector<int> output(arr.size());

    for (int x : arr) { ++g_iterations; count[x - minVal]++; }
    for (int i = 1; i < range; ++i) { ++g_iterations; count[i] += count[i-1]; }
    for (int i = (int)arr.size()-1; i >= 0; --i) {
        ++g_iterations;
        output[--count[arr[i] - minVal]] = arr[i];
    }
    arr = output;
}
