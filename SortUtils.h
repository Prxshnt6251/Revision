#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>
#include <functional>
#include <numeric>

// ─────────────────────────────────────────────────────────────────────────────
// Global iteration counter (reset before each sort call)
// ─────────────────────────────────────────────────────────────────────────────
extern long long g_iterations;

// ─────────────────────────────────────────────────────────────────────────────
// Benchmark result structure
// ─────────────────────────────────────────────────────────────────────────────
struct BenchmarkResult {
    std::string algorithmName;
    std::string dataStructureType;   // e.g. "Random Array", "Nearly Sorted", etc.
    int inputSize;
    std::vector<int> input;          // first 10 elements shown
    std::vector<int> output;         // first 10 elements shown
    long long iterations;
    double timeMs;
    std::string theoreticalComplexity;
    std::string theorem;             // "Master's Theorem" or "Akra-Bazzi"
    std::string complexityProof;     // brief derivation string
};

// ─────────────────────────────────────────────────────────────────────────────
// Pretty printer
// ─────────────────────────────────────────────────────────────────────────────
inline void printResult(const BenchmarkResult& r) {
    const int W = 72;
    std::string border(W, '=');
    std::string thin(W, '-');

    std::cout << "\n" << border << "\n";
    std::cout << "  Algorithm      : " << r.algorithmName << "\n";
    std::cout << "  Data Type      : " << r.dataStructureType << "\n";
    std::cout << "  Input Size (n) : " << r.inputSize << "\n";
    std::cout << thin << "\n";

    // Show first 10 elements
    auto showVec = [](const std::vector<int>& v, const std::string& label) {
        std::cout << "  " << label << " : [ ";
        int lim = std::min((int)v.size(), 10);
        for (int i = 0; i < lim; ++i) std::cout << v[i] << (i+1<lim?", ":"");
        if ((int)v.size() > 10) std::cout << " ... (" << v.size()-10 << " more)";
        std::cout << " ]\n";
    };
    showVec(r.input,  "Input (first 10) ");
    showVec(r.output, "Output(first 10) ");

    std::cout << thin << "\n";
    std::cout << "  Time Taken     : " << std::fixed << std::setprecision(4)
              << r.timeMs << " ms\n";
    std::cout << "  Iterations     : " << r.iterations << "\n";
    std::cout << thin << "\n";
    std::cout << "  Complexity     : " << r.theoreticalComplexity << "\n";
    std::cout << "  Theorem Used   : " << r.theorem << "\n";
    std::cout << "  Proof Sketch   : " << r.complexityProof << "\n";
    std::cout << border << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// Data-set generators
// ─────────────────────────────────────────────────────────────────────────────
inline std::vector<int> makeRandom(int n, int seed = 42) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, 10*n);
    std::vector<int> v(n);
    for (auto& x : v) x = dist(rng);
    return v;
}

inline std::vector<int> makeSorted(int n) {
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 1);
    return v;
}

inline std::vector<int> makeReverseSorted(int n) {
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 1);
    std::reverse(v.begin(), v.end());
    return v;
}

inline std::vector<int> makeNearlySorted(int n, int seed = 7) {
    std::vector<int> v = makeSorted(n);
    std::mt19937 rng(seed);
    int swaps = std::max(1, n/10);
    std::uniform_int_distribution<int> dist(0, n-1);
    for (int i = 0; i < swaps; ++i)
        std::swap(v[dist(rng)], v[dist(rng)]);
    return v;
}

inline std::vector<int> makeAllSame(int n) {
    return std::vector<int>(n, 42);
}

// ─────────────────────────────────────────────────────────────────────────────
// Timer helper
// ─────────────────────────────────────────────────────────────────────────────
inline double measureMs(std::function<void()> fn) {
    auto t0 = std::chrono::high_resolution_clock::now();
    fn();
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}
