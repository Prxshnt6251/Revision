# ═══════════════════════════════════════════════════════════════════
#  Makefile — Sorting Algorithms Benchmark
#  Usage:
#    make          → compile
#    make run      → compile and run
#    make clean    → remove build artefacts
# ═══════════════════════════════════════════════════════════════════

CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -I.

SRCS := main.cpp \
        algorithms/bubbleSort.cpp \
        algorithms/selectionSort.cpp \
        algorithms/insertionSort.cpp \
        algorithms/binaryInsertionSort.cpp \
        algorithms/shellSort.cpp \
        algorithms/mergeSort.cpp \
        algorithms/quickSort.cpp \
        algorithms/heapSort.cpp \
        algorithms/timSort.cpp \
        algorithms/bitonicSort.cpp \
        algorithms/introSort.cpp \
        algorithms/countingSort.cpp \
        algorithms/radixSort.cpp

TARGET := sort_bench

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
