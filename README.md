# Sorting Algorithms — Benchmark & Complexity Verification  
**C++17 · 13 algorithms · 5 data-set types · Master's Theorem + Akra-Bazzi**

---

## Project Structure

```
sorting_algorithms/
│
├── include/
│   └── SortUtils.h           ← shared types, timer, data generators, printer
│
├── algorithms/
│   ├── bubbleSort.cpp         O(n²) / O(n) best
│   ├── selectionSort.cpp      Θ(n²) always
│   ├── insertionSort.cpp      O(n²) / Ω(n)
│   ├── binaryInsertionSort.cpp  O(n²) shifts, O(n log n) comparisons
│   ├── shellSort.cpp          O(n^{3/2})  Knuth gaps
│   ├── mergeSort.cpp          Θ(n log n)  Master's Thm Case 2
│   ├── quickSort.cpp          Θ(n log n) avg  Master's Thm Case 2
│   ├── heapSort.cpp           Θ(n log n)  Master's Thm on heapify
│   ├── timSort.cpp            Θ(n log n)  Akra-Bazzi
│   ├── bitonicSort.cpp        Θ(n log²n)  Akra-Bazzi
│   ├── introSort.cpp          O(n log n)  Hybrid (QS + HS + IS)
│   ├── countingSort.cpp       Θ(n + k)    linear, non-comparison
│   └── radixSort.cpp          Θ(d·(n+b))  linear, non-comparison
│
├── main.cpp                   ← master benchmark driver
├── Makefile
└── README.md
```

---

## Compile & Run

```bash
# Using Makefile
make
./sort_bench

# Or directly with g++
g++ -std=c++17 -O2 -I. -o sort_bench main.cpp algorithms/*.cpp
./sort_bench
```

---

## What `main.cpp` does

`main.cpp` runs **four benchmark parts**:

### Part 1 — Per-Algorithm Detailed Report
For every algorithm × every data-set type, prints:

| Field           | Description                              |
|-----------------|------------------------------------------|
| Input (first 10)| First 10 elements of the input array     |
| Output (first 10)| First 10 elements after sorting         |
| Time Taken      | Wall-clock time in milliseconds          |
| Iterations      | Exact comparison / swap count            |
| Complexity      | Theoretical big-O / big-Θ               |
| Theorem Used    | Master's Theorem or Akra-Bazzi           |
| Proof Sketch    | Brief mathematical derivation            |

### Part 2 — Summary Table
One-line per algorithm at n = 2000 (random array), side-by-side comparison.

### Part 3 — Empirical Growth-Rate Verification
Runs each algorithm at n = 250, 500, 1000, 2000 and prints:
- **Iter/n²** — stable → O(n²) algorithm  
- **Iter/(n log n)** — stable → O(n log n) algorithm

This empirically **verifies** the theoretical complexity claims.

### Part 4 — Correctness Assertions
Unit-tests each algorithm on 7 edge cases (empty, single, duplicates, reverse, sorted, large random).  
Reports `X/Y tests passed ✓`.

### Part 5 — Theorem Reference Card
Prints Master's Theorem and Akra-Bazzi Theorem statement for quick reference.

---

## Data-Set Types

| Type              | Description                              |
|-------------------|------------------------------------------|
| Random Array      | Uniformly random integers                |
| Sorted Array      | Already in ascending order               |
| Reverse Sorted    | In descending order (worst case for QS)  |
| Nearly Sorted     | ~10% random swaps on sorted array        |
| All Same Elements | Every element identical                  |

---

## Complexity Quick-Reference

```
Algorithm            Best        Average      Worst       Stable  Space
─────────────────────────────────────────────────────────────────────────
Bubble Sort          O(n)        O(n²)        O(n²)       YES     O(1)
Selection Sort       O(n²)       O(n²)        O(n²)       NO      O(1)
Insertion Sort       O(n)        O(n²)        O(n²)       YES     O(1)
Binary Ins. Sort     O(n)        O(n²)        O(n²)       YES     O(log n)
Shell Sort           O(n log n)  O(n^{3/2})   O(n^{3/2})  NO      O(1)
Merge Sort           O(n log n)  O(n log n)   O(n log n)  YES     O(n)
Quick Sort (rand)    O(n log n)  O(n log n)   O(n²)       NO      O(log n)
Heap Sort            O(n log n)  O(n log n)   O(n log n)  NO      O(1)
Tim Sort             O(n)        O(n log n)   O(n log n)  YES     O(n)
Bitonic Sort         O(n log²n)  O(n log²n)   O(n log²n)  NO      O(log²n)
Intro Sort           O(n log n)  O(n log n)   O(n log n)  NO      O(log n)
Counting Sort        O(n + k)    O(n + k)     O(n + k)    YES     O(n + k)
Radix Sort           O(d(n+b))   O(d(n+b))    O(d(n+b))   YES     O(n + b)
─────────────────────────────────────────────────────────────────────────
```

---

## Theorem Reference

### Master's Theorem
For `T(n) = a·T(n/b) + f(n)`, where `a ≥ 1`, `b > 1`:

| Case | Condition                         | Result                        |
|------|-----------------------------------|-------------------------------|
| 1    | f(n) = O(n^{log_b(a) − ε})       | T(n) = Θ(n^{log_b(a)})        |
| 2    | f(n) = Θ(n^{log_b(a)})           | T(n) = Θ(n^{log_b(a)} · log n)|
| 3    | f(n) = Ω(n^{log_b(a) + ε})       | T(n) = Θ(f(n))                |

**Merge Sort example:**  
`T(n) = 2T(n/2) + n`, a=2, b=2, log₂(2)=1, f(n)=n=Θ(n¹) → **Case 2** → `T(n) = Θ(n log n)` ✓

### Akra-Bazzi Theorem
For `T(n) = Σ aᵢ·T(n/bᵢ) + g(n)`:

Find `p` such that `Σ aᵢ · bᵢ^{-p} = 1`, then:

```
T(n) = Θ( n^p · (1 + ∫₁ⁿ g(u)/u^{p+1} du) )
```

**Tim Sort merge phase example:**  
`T(n) = 2T(n/2) + n·log n`, p=1:  
∫₁ⁿ (u log u)/u² du = ∫₁ⁿ (log u)/u du = (log n)²/2  
→ `T(n) = Θ(n · (log n)²)` — but Tim Sort exploits natural runs → Θ(n log n) ✓

**Bitonic Sort example:**  
`T_sort(n) = 2T(n/2) + Θ(n log n)`, p=1:  
∫₁ⁿ (log u)/u du = (log n)²/2  
→ `T(n) = Θ(n log²n)` ✓

---

## Design Decisions

- **Global `g_iterations`** — reset before each call, incremented at every comparison/swap inside each algorithm, giving an exact operation count.
- **`extern long long g_iterations`** — declared in each `.cpp` file, defined once in `main.cpp` to avoid multiple-definition linker errors.
- **Randomised pivot in Quick Sort** — avoids adversarial inputs; `srand(42)` for reproducibility.
- **Bitonic Sort padding** — padded to next power-of-2 with `INT_MAX` sentinels, stripped after sort.
- **Counting / Radix Sort** handle negative integers by shifting the range.

---

*Built as a teaching reference for algorithm analysis courses.*
