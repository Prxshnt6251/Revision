/*
 * ╔══════════════════════════════════════════════════════════════════════════╗
 * ║                    SORTING ALGORITHMS BENCHMARK                         ║
 * ║              Time Complexity Verification via Empirical Testing          ║
 * ║                                                                          ║
 * ║  Algorithms tested:                                                      ║
 * ║    1. Bubble Sort          — O(n²)        [Master's Thm / series]        ║
 * ║    2. Selection Sort       — Θ(n²)        [series argument]              ║
 * ║    3. Insertion Sort       — O(n²)/O(n)   [best/worst]                   ║
 * ║    4. Binary Insertion Sort— O(n²)/O(n logn) comparisons                 ║
 * ║    5. Shell Sort           — O(n^{3/2})   [Knuth gap, Akra-Bazzi]        ║
 * ║    6. Merge Sort           — Θ(n log n)   [Master's Thm Case 2]          ║
 * ║    7. Quick Sort           — Θ(n log n)   [Master's Thm Case 2, avg]     ║
 * ║    8. Heap Sort            — Θ(n log n)   [Master's Thm on heapify]      ║
 * ║    9. Tim Sort             — Θ(n log n)   [Akra-Bazzi on merge phase]    ║
 * ║   10. Bitonic Sort         — Θ(n log²n)   [Akra-Bazzi]                   ║
 * ║   11. Intro Sort           — O(n log n)   [Master's Thm + hybrid]        ║
 * ║   12. Counting Sort        — Θ(n + k)     [linear, non-comparison]       ║
 * ║   13. Radix Sort           — Θ(d·(n+b))  [linear, non-comparison]       ║
 * ║                                                                          ║
 * ║  Data structures tested:                                                 ║
 * ║    • Random Array                                                        ║
 * ║    • Already Sorted Array                                                ║
 * ║    • Reverse Sorted Array                                                ║
 * ║    • Nearly Sorted Array                                                 ║
 * ║    • All-Same-Elements Array                                             ║
 * ║                                                                          ║
 * ║  Compile:  g++ -O2 -std=c++17 -o sort_bench main.cpp                    ║
 * ║            algorithms/*.cpp                                              ║
 * ╚══════════════════════════════════════════════════════════════════════════╝
 */

#include "include/SortUtils.h"
#include <map>
#include <cassert>
#include <cmath>

// ── Global iteration counter (defined here, extern in all algorithm files) ──
long long g_iterations = 0;

// ── Forward declarations ──────────────────────────────────────────────────────
void bubbleSort         (std::vector<int>&);
void selectionSort      (std::vector<int>&);
void insertionSort      (std::vector<int>&);
void binaryInsertionSort(std::vector<int>&);
void shellSort          (std::vector<int>&);
void mergeSort          (std::vector<int>&);
void quickSort          (std::vector<int>&);
void heapSort           (std::vector<int>&);
void timSort            (std::vector<int>&);
void bitonicSort        (std::vector<int>&);
void introSort          (std::vector<int>&);
void countingSort       (std::vector<int>&);
void radixSort          (std::vector<int>&);

// ── Algorithm metadata ────────────────────────────────────────────────────────
struct AlgoMeta {
    std::string name;
    std::function<void(std::vector<int>&)> fn;
    std::string complexity;
    std::string theorem;
    std::string proof;
};

// ── Verify correctness ────────────────────────────────────────────────────────
bool isSorted(const std::vector<int>& v) {
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i] < v[i-1]) return false;
    return true;
}

// ── Run one algorithm on one dataset ─────────────────────────────────────────
BenchmarkResult runBenchmark(
    const AlgoMeta&          algo,
    const std::vector<int>&  data,
    const std::string&       dataLabel)
{
    std::vector<int> arr = data;   // copy — don't modify original
    g_iterations = 0;

    double ms = measureMs([&]() { algo.fn(arr); });

    if (!isSorted(arr)) {
        std::cerr << "[ERROR] " << algo.name
                  << " failed to sort " << dataLabel << "!\n";
    }

    BenchmarkResult r;
    r.algorithmName       = algo.name;
    r.dataStructureType   = dataLabel;
    r.inputSize           = (int)data.size();
    r.input               = data;
    r.output              = arr;
    r.iterations          = g_iterations;
    r.timeMs              = ms;
    r.theoreticalComplexity = algo.complexity;
    r.theorem             = algo.theorem;
    r.complexityProof     = algo.proof;
    return r;
}

// ── Complexity verification helpers ──────────────────────────────────────────
void printComplexityTable(const std::string& algoName,
                          const std::vector<std::pair<int,long long>>& points) {
    std::cout << "\n  ┌─ Empirical Growth Rate — " << algoName << " ─┐\n";
    std::cout << "  │  n         │  Iterations   │  Iter/n²     │  Iter/(nlogn) │\n";
    std::cout << "  ├────────────┼───────────────┼──────────────┼───────────────┤\n";
    for (auto& [n, iters] : points) {
        double n2      = (double)n * n;
        double nlogn   = (double)n * std::log2(n);
        std::cout << "  │ " << std::setw(10) << n
                  << " │ " << std::setw(13) << iters
                  << " │ " << std::setw(12) << std::fixed << std::setprecision(4)
                  << (double)iters / n2
                  << " │ " << std::setw(13) << (double)iters / nlogn
                  << " │\n";
    }
    std::cout << "  └────────────┴───────────────┴──────────────┴───────────────┘\n";
    std::cout << "  (Stable column → complexity class; if Iter/n² stable → O(n²),"
                 " if Iter/(nlogn) stable → O(n log n))\n";
}

// ── Master summary table ──────────────────────────────────────────────────────
void printSummaryTable(const std::vector<BenchmarkResult>& results) {
    std::cout << "\n\n";
    std::string sep(100, '=');
    std::cout << sep << "\n";
    std::cout << "  SUMMARY TABLE  —  n = " << results[0].inputSize << "  ("
              << results[0].dataStructureType << ")\n";
    std::cout << sep << "\n";
    std::cout << std::left
              << std::setw(25) << "Algorithm"
              << std::setw(18) << "Complexity"
              << std::setw(18) << "Theorem"
              << std::setw(14) << "Time (ms)"
              << std::setw(16) << "Iterations"
              << "Correct?\n";
    std::cout << std::string(100, '-') << "\n";
    for (auto& r : results) {
        std::cout << std::left
                  << std::setw(25) << r.algorithmName
                  << std::setw(18) << r.theoreticalComplexity
                  << std::setw(18) << r.theorem
                  << std::setw(14) << std::fixed << std::setprecision(4) << r.timeMs
                  << std::setw(16) << r.iterations
                  << "✓\n";
    }
    std::cout << sep << "\n";
}

// ═════════════════════════════════════════════════════════════════════════════
//  MAIN
// ═════════════════════════════════════════════════════════════════════════════
int main() {
    std::cout << R"(
╔══════════════════════════════════════════════════════════════════════════╗
║          SORTING ALGORITHMS — BENCHMARK & COMPLEXITY VERIFICATION        ║
╚══════════════════════════════════════════════════════════════════════════╝
)";

    // ── Algorithm registry ────────────────────────────────────────────────
    std::vector<AlgoMeta> algorithms = {
        {
            "Bubble Sort", bubbleSort,
            "O(n²) / O(n) best",
            "Arithmetic Series",
            "T(n)=T(n-1)+(n-1) => sum_{k=1}^{n-1}k = n(n-1)/2 = Θ(n²)"
        },
        {
            "Selection Sort", selectionSort,
            "Θ(n²) always",
            "Arithmetic Series",
            "Always n(n-1)/2 comparisons regardless of input => Θ(n²)"
        },
        {
            "Insertion Sort", insertionSort,
            "O(n²) / Ω(n)",
            "Telescoping Recurrence",
            "Worst: T(n)=T(n-1)+(n-1)=>Θ(n²); Best: T(n)=T(n-1)+1=>Θ(n)"
        },
        {
            "Binary Insertion Sort", binaryInsertionSort,
            "O(n²) shifts, O(nlogn) cmp",
            "Master's Theorem (search)",
            "Search: T(n)=T(n/2)+1, a=1,b=2,log_b(a)=0 => Θ(logn)/search"
        },
        {
            "Shell Sort", shellSort,
            "O(n^{3/2}) Knuth gaps",
            "Akra-Bazzi (approx)",
            "d passes of O(n) work each; Knuth gap => O(n^{4/3}) to O(n^{3/2})"
        },
        {
            "Merge Sort", mergeSort,
            "Θ(n log n)",
            "Master's Theorem",
            "T(n)=2T(n/2)+n; a=2,b=2,log_b(a)=1=f(n) => Case2 => Θ(nlogn)"
        },
        {
            "Quick Sort", quickSort,
            "Θ(n log n) avg, O(n²) worst",
            "Master's Theorem",
            "Avg: T(n)=2T(n/2)+n => Case2 => Θ(nlogn); randomised pivot"
        },
        {
            "Heap Sort", heapSort,
            "Θ(n log n) all cases",
            "Master's Theorem",
            "heapify: T(n)=T(2n/3)+1 => a=1,b=3/2,p=0 => O(logn); n calls"
        },
        {
            "Tim Sort", timSort,
            "Θ(n log n) / Θ(n) best",
            "Akra-Bazzi Theorem",
            "p=1: T(n)=Θ(n(1+∫ln(u)/u du))=Θ(nlogn); best=Θ(n) sorted runs"
        },
        {
            "Bitonic Sort", bitonicSort,
            "Θ(n log²n)",
            "Akra-Bazzi Theorem",
            "T_s: 2T_s(n/2)+Θ(nlogn),p=1,∫logu/u du=(logn)²/2=>Θ(nlog²n)"
        },
        {
            "Intro Sort", introSort,
            "O(n log n) worst case",
            "Master's Theorem + Hybrid",
            "QS avg Θ(nlogn) + HS fallback at depth 2logn => O(nlogn) always"
        },
        {
            "Counting Sort", countingSort,
            "Θ(n + k)",
            "Direct Analysis",
            "3 passes over count[k] + 2 passes over n; non-comparison => Θ(n+k)"
        },
        {
            "Radix Sort", radixSort,
            "Θ(d·(n + base))",
            "Direct Analysis",
            "d=digits, d passes of Θ(n+base) counting sort each => Θ(d(n+b))"
        },
    };

    // ── Dataset definitions ───────────────────────────────────────────────
    const int N = 2000;

    struct DataSet { std::string label; std::vector<int> data; };
    std::vector<DataSet> datasets = {
        { "Random Array",        makeRandom(N)        },
        { "Sorted Array",        makeSorted(N)        },
        { "Reverse Sorted Array",makeReverseSorted(N) },
        { "Nearly Sorted Array", makeNearlySorted(N)  },
        { "All Same Elements",   makeAllSame(N)       },
    };

    // ════════════════════════════════════════════════════════════════════
    // PART 1 — Full benchmark on every algorithm × every dataset
    // ════════════════════════════════════════════════════════════════════
    std::cout << "\n╔══ PART 1: Per-Algorithm Detailed Report ══╗\n";

    for (auto& algo : algorithms) {
        std::cout << "\n\n▶▶▶  " << algo.name << "  ◀◀◀\n";
        std::cout << "    Complexity : " << algo.complexity << "\n";
        std::cout << "    Theorem    : " << algo.theorem    << "\n";
        std::cout << "    Proof      : " << algo.proof      << "\n";

        for (auto& ds : datasets) {
            BenchmarkResult r = runBenchmark(algo, ds.data, ds.label);
            printResult(r);
        }
    }

    // ════════════════════════════════════════════════════════════════════
    // PART 2 — Summary table: all algorithms on random data
    // ════════════════════════════════════════════════════════════════════
    std::cout << "\n\n╔══ PART 2: Summary Table (Random Array, n=" << N << ") ══╗\n";
    {
        std::vector<BenchmarkResult> summaryResults;
        for (auto& algo : algorithms)
            summaryResults.push_back(runBenchmark(algo, datasets[0].data, datasets[0].label));
        printSummaryTable(summaryResults);
    }

    // ════════════════════════════════════════════════════════════════════
    // PART 3 — Empirical growth-rate verification
    //          Run each algorithm at n = 250, 500, 1000, 2000
    //          and show how iterations scale → verifies O(?) claim
    // ════════════════════════════════════════════════════════════════════
    std::cout << "\n\n╔══ PART 3: Empirical Growth-Rate Verification ══╗\n";
    std::cout << "(Sorted 'Random Array' at multiple sizes; check which column stays stable)\n";

    std::vector<int> sizes = {250, 500, 1000, 2000};

    for (auto& algo : algorithms) {
        std::vector<std::pair<int,long long>> growthPoints;
        for (int sz : sizes) {
            std::vector<int> arr = makeRandom(sz, 99);
            g_iterations = 0;
            algo.fn(arr);
            growthPoints.push_back({sz, g_iterations});
        }
        printComplexityTable(algo.name, growthPoints);
    }

    // ════════════════════════════════════════════════════════════════════
    // PART 4 — Correctness assertions (unit tests)
    // ════════════════════════════════════════════════════════════════════
    std::cout << "\n\n╔══ PART 4: Correctness Assertions ══╗\n";
    {
        auto testCases = {
            std::vector<int>{},
            std::vector<int>{42},
            std::vector<int>{3, 1, 2},
            std::vector<int>{5, 5, 5, 5},
            std::vector<int>{9, 7, 5, 3, 1},
            std::vector<int>{1, 2, 3, 4, 5},
            makeRandom(500, 7),
        };

        int passed = 0, total = 0;
        for (auto& algo : algorithms) {
            for (auto tc : testCases) {
                std::vector<int> ref = tc;
                std::sort(ref.begin(), ref.end());

                std::vector<int> arr = tc;
                g_iterations = 0;
                algo.fn(arr);

                ++total;
                if (arr == ref) {
                    ++passed;
                } else {
                    std::cout << "[FAIL] " << algo.name
                              << " on size " << tc.size() << "\n";
                }
            }
        }
        std::cout << "  Result: " << passed << "/" << total
                  << " tests passed";
        if (passed == total) std::cout << "  ✓ ALL CORRECT\n";
        else                 std::cout << "  ✗ SOME FAILED\n";
    }

    // ════════════════════════════════════════════════════════════════════
    // PART 5 — Complexity theorem cheat-sheet
    // ════════════════════════════════════════════════════════════════════
    std::cout << R"(

╔══════════════════════════════════════════════════════════════════════════════╗
║                  COMPLEXITY THEOREM REFERENCE                               ║
╠══════════════════════════════════════════════════════════════════════════════╣
║  MASTER'S THEOREM  T(n) = a·T(n/b) + f(n),  a≥1, b>1                       ║
║  ─────────────────────────────────────────────────────────────────────────  ║
║  Case 1: f(n) = O(n^{log_b(a)-ε})  →  T(n) = Θ(n^{log_b(a)})              ║
║  Case 2: f(n) = Θ(n^{log_b(a)})   →  T(n) = Θ(n^{log_b(a)} log n)         ║
║  Case 3: f(n) = Ω(n^{log_b(a)+ε}) →  T(n) = Θ(f(n))  [regularity cond.]   ║
║                                                                              ║
║  AKRA-BAZZI THEOREM  T(n) = Σ a_i·T(n/b_i) + g(n)                          ║
║  ─────────────────────────────────────────────────────────────────────────  ║
║  Find p: Σ a_i / b_i^p = 1                                                  ║
║  T(n) = Θ( n^p · (1 + ∫_1^n g(u)/u^{p+1} du) )                            ║
║  Advantage: handles unequal splits (e.g. bitonicSort, shellSort)             ║
║                                                                              ║
║  COMPARISON-SORT LOWER BOUND                                                 ║
║  ─────────────────────────────────────────────────────────────────────────  ║
║  Any comparison sort requires Ω(n log n) comparisons (decision-tree arg.)   ║
║  Counting / Radix sort bypass this by exploiting integer structure.          ║
╚══════════════════════════════════════════════════════════════════════════════╝
)";

    return 0;
}
