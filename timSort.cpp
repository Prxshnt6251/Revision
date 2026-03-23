/*
 * ═══════════════════════════════════════════════════════════════════
 *  timSort.cpp  —  Tim Sort  (simplified)
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Hybrid of merge sort and insertion sort (used in Python / Java).
 *  1. Divide the array into "runs" of size RUN (typically 32 or 64).
 *  2. Sort each run with insertion sort.
 *  3. Merge runs with merge sort.
 *
 *  RECURRENCE  (Akra-Bazzi / merge phase)
 *  ───────────────────────────────────────
 *  Merge phase: T(n) = 2·T(n/2) + Θ(n)
 *
 *  AKRA-BAZZI METHOD  (illustrating alternative to Master's Thm)
 *  ──────────────────────────────────────────────────────────────
 *  g(n) = n,  a_i = 2,  b_i = 1/2
 *  Find p: a_i * (1/b_i)^p = 1  →  2 * 2^{-p} = 1  →  p = 1
 *  T(n) = Θ(n^p (1 + ∫_1^n g(u)/u^{p+1} du))
 *       = Θ(n   (1 + ∫_1^n u/u² du))
 *       = Θ(n   (1 + ln n))
 *       = Θ(n log n)
 *
 *  Best case (already sorted runs): Θ(n)
 *  Worst / Average               : Θ(n log n)
 *
 *  SPACE : O(n) auxiliary
 *  STABLE: YES
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"

extern long long g_iterations;

static const int RUN = 32;

static void insertionSortRange(std::vector<int>& arr, int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        int key = arr[i];
        int j   = i - 1;
        while (j >= l && arr[j] > key) {
            ++g_iterations;
            arr[j+1] = arr[j];
            --j;
        }
        ++g_iterations;
        arr[j+1] = key;
    }
}

static void mergeRuns(std::vector<int>& arr, int l, int m, int r) {
    std::vector<int> left (arr.begin() + l, arr.begin() + m + 1);
    std::vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < (int)left.size() && j < (int)right.size()) {
        ++g_iterations;
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else                     arr[k++] = right[j++];
    }
    while (i < (int)left.size())  { ++g_iterations; arr[k++] = left[i++];  }
    while (j < (int)right.size()) { ++g_iterations; arr[k++] = right[j++]; }
}

void timSort(std::vector<int>& arr) {
    int n = arr.size();
    // Step 1: Sort individual runs
    for (int i = 0; i < n; i += RUN)
        insertionSortRange(arr, i, std::min(i + RUN - 1, n - 1));

    // Step 2: Merge runs
    for (int size = RUN; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid   = std::min(left + size - 1,     n - 1);
            int right = std::min(left + 2 * size - 1, n - 1);
            if (mid < right)
                mergeRuns(arr, left, mid, right);
        }
    }
}
