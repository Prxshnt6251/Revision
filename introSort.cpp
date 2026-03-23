/*
 * ═══════════════════════════════════════════════════════════════════
 *  introSort.cpp  —  Intro Sort  (Introspective Sort)
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Hybrid of Quick Sort, Heap Sort, and Insertion Sort (used in
 *  std::sort in most C++ standard library implementations).
 *
 *  Strategy:
 *  • Start with Quick Sort (fast average case).
 *  • Switch to Heap Sort if recursion depth > 2·log₂(n)
 *    to guarantee O(n log n) worst case.
 *  • Switch to Insertion Sort for small subarrays (size ≤ 16).
 *
 *  RECURRENCE  (Quick Sort phase, average)
 *  ──────────────────────────────────────
 *  T(n) = 2·T(n/2) + Θ(n)
 *  Master's Theorem Case 2:  T(n) = Θ(n log n)
 *
 *  WORST CASE  (Heap Sort fallback)
 *  ─────────────────────────────────
 *  Heap Sort ensures Θ(n log n) always.
 *  Combined: O(n log n) worst case, O(n log n) average.
 *
 *  SPACE : O(log n) stack (depth-limited recursion)
 *  STABLE: NO
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"
#include <cmath>

extern long long g_iterations;

// ── Insertion sort on arr[lo..hi] ────────────────────────────────
static void isort(std::vector<int>& arr, int lo, int hi) {
    for (int i = lo + 1; i <= hi; ++i) {
        int key = arr[i], j = i - 1;
        while (j >= lo && arr[j] > key) {
            ++g_iterations;
            arr[j + 1] = arr[j];
            --j;
        }
        ++g_iterations;
        arr[j + 1] = key;
    }
}

// ── Heap sort on arr[lo..hi] iterative siftDown (0-based virtual heap) ──
static void siftDown(std::vector<int>& arr, int lo, int heapLen, int root) {
    while (true) {
        int largest = root;
        int l = 2 * root + 1;
        int r = 2 * root + 2;
        ++g_iterations;
        if (l < heapLen && arr[lo + l] > arr[lo + largest]) largest = l;
        ++g_iterations;
        if (r < heapLen && arr[lo + r] > arr[lo + largest]) largest = r;
        if (largest == root) break;
        std::swap(arr[lo + root], arr[lo + largest]);
        root = largest;
    }
}

static void hsort(std::vector<int>& arr, int lo, int hi) {
    int n = hi - lo + 1;
    for (int i = n / 2 - 1; i >= 0; --i)
        siftDown(arr, lo, n, i);
    for (int end = n - 1; end > 0; --end) {
        std::swap(arr[lo], arr[lo + end]);
        siftDown(arr, lo, end, 0);
    }
}

// ── Median-of-three: ensures pivot = median of lo/mid/hi ─────────
static void medianPivot(std::vector<int>& arr, int lo, int hi) {
    int mid = lo + (hi - lo) / 2;
    if (arr[lo]  > arr[mid]) std::swap(arr[lo],  arr[mid]);
    if (arr[lo]  > arr[hi])  std::swap(arr[lo],  arr[hi]);
    if (arr[mid] > arr[hi])  std::swap(arr[mid], arr[hi]);
    std::swap(arr[mid], arr[hi]); // move median to hi as pivot
}

static int qpartition(std::vector<int>& arr, int lo, int hi) {
    medianPivot(arr, lo, hi);
    int pivot = arr[hi], i = lo - 1;
    for (int j = lo; j < hi; ++j) {
        ++g_iterations;
        if (arr[j] <= pivot) std::swap(arr[++i], arr[j]);
    }
    std::swap(arr[i + 1], arr[hi]);
    return i + 1;
}

// ── Recursive intro-sort core ─────────────────────────────────────
static void introCore(std::vector<int>& arr, int lo, int hi, int depthLimit) {
    while (lo < hi) {
        int size = hi - lo + 1;
        if (size <= 16) { isort(arr, lo, hi); return; }
        if (depthLimit == 0) { hsort(arr, lo, hi); return; }
        int pi = qpartition(arr, lo, hi);
        if (pi - lo < hi - pi) {
            introCore(arr, lo, pi - 1, depthLimit - 1);
            lo = pi + 1;
        } else {
            introCore(arr, pi + 1, hi, depthLimit - 1);
            hi = pi - 1;
        }
        --depthLimit;
    }
}

void introSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    int depthLimit = 2 * (int)std::log2((double)arr.size());
    introCore(arr, 0, (int)arr.size() - 1, depthLimit);
}
