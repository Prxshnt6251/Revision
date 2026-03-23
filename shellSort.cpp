/*
 * ═══════════════════════════════════════════════════════════════════
 *  shellSort.cpp  —  Shell Sort  (Knuth gap sequence)
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Generalisation of insertion sort that allows exchange of items
 *  far apart. Uses a decreasing sequence of gaps (Knuth: 1, 4, 13,
 *  40, 121, …  i.e. h = 3h+1).  When gap = 1 it reduces to plain
 *  insertion sort on an almost-sorted array.
 *
 *  RECURRENCE / COMPLEXITY
 *  ───────────────────────
 *  Exact recurrence depends on gap sequence. For Knuth's sequence:
 *    T(n) = O(n^{3/2})   (tight empirical / proven upper bound)
 *
 *  AKRA-BAZZI THEOREM (illustrative for gap-halving sequence h=n/2):
 *  ──────────────────────────────────────────────────────────────────
 *  Each "pass" at gap g does O(n) work.
 *  Number of passes ≈ log_2 n.
 *  Total: Σ O(n) over O(log n) passes → O(n log n) best case.
 *  Worst case (Hibbard gaps): Θ(n^{3/2});  Knuth: O(n^{4/3}).
 *
 *  SPACE : O(1) auxiliary
 *  STABLE: NO
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"

extern long long g_iterations;

void shellSort(std::vector<int>& arr) {
    int n = arr.size();

    // Generate Knuth gap sequence
    int gap = 1;
    while (gap < n / 3) gap = 3 * gap + 1;

    for (; gap >= 1; gap /= 3) {
        // Insertion sort with this gap
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j    = i;
            while (j >= gap && arr[j - gap] > temp) {
                ++g_iterations;
                arr[j] = arr[j - gap];
                j -= gap;
            }
            ++g_iterations;
            arr[j] = temp;
        }
    }
}
