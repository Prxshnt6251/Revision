/*
 * ═══════════════════════════════════════════════════════════════════
 *  heapSort.cpp  —  Heap Sort
 * ═══════════════════════════════════════════════════════════════════
 *
 *  ALGORITHM
 *  ---------
 *  Phase 1 — Build a max-heap from the array in O(n).
 *  Phase 2 — Repeatedly extract the maximum (root), place it at the
 *             end, and restore the heap property.
 *
 *  RECURRENCE
 *  ──────────
 *  heapify  : T(n) = T(2n/3) + O(1)
 *
 *  MASTER'S THEOREM  (Case 2 / Case 3 boundary — actually Case 2)
 *  ──────────────────────────────────────────────────────────────
 *  a = 1,  b = 3/2,  f(n) = 1
 *  log_{3/2}(1) = 0
 *  f(n) = Θ(n^0) = Θ(1)  →  Case 2:  heapify = O(log n)
 *
 *  Full sort: n heapify calls  →  T(n) = O(n log n) all cases
 *
 *  SPACE : O(1) auxiliary (in-place)
 *  STABLE: NO
 * ═══════════════════════════════════════════════════════════════════
 */

#include "include/SortUtils.h"

extern long long g_iterations;

static void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    ++g_iterations;
    if (l < n && arr[l] > arr[largest]) largest = l;
    ++g_iterations;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    // Build max-heap
    for (int i = n/2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    // Extract elements
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
