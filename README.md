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
