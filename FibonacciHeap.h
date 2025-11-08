#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include "Task.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

struct FibNode {
    Task task;
    int degree;
    bool mark;
    FibNode* parent;
    FibNode* child;
    FibNode* left;
    FibNode* right;

    explicit FibNode(const Task& t)
        : task(t), degree(0), mark(false),
          parent(nullptr), child(nullptr), left(this), right(this) {}
};

class FibonacciHeap {
private:
    FibNode* minNode;
    int nodeCount;

    // Helpers
    void link(FibNode* y, FibNode* x);
    void consolidate();
    void cut(FibNode* x, FibNode* y);
    void cascadingCut(FibNode* y);

public:
    FibonacciHeap();

    // Core operations
    void insertTask(const Task& t);
    Task extractHighestPriority();
    void decreaseTaskPriority(int id, int newPriority);
    const Task* findById(int id) const;

    // Utilities
    bool isEmpty() const;
    void displayHeap() const;
};

#endif // FIBONACCI_HEAP_H
