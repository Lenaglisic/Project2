//
// Created by Lena Glisic on 11/3/25.
//

#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <string>

// Task structure
struct Task {
    int id;
    std::string name;
    int priority;
    int startTime;
    int duration;
    int deadline;

    Task(int id_, std::string name_, int priority_, int start_, int dur_, int dead_)
        : id(id_), name(std::move(name_)), priority(priority_),
          startTime(start_), duration(dur_), deadline(dead_) {}
};

// Node used by Fibonacci Heap
struct FibNode {
    Task task;
    FibNode* parent;
    FibNode* child;
    FibNode* left;
    FibNode* right;
    int degree;
    bool mark;

    explicit FibNode(const Task& t)
        : task(t), parent(nullptr), child(nullptr),
          left(this), right(this), degree(0), mark(false) {}
};

// Fibonacci Heap class definition
class FibonacciHeap {
private:
    FibNode* minNode;  // pointer to node with highest priority (lowest key)
    int nodeCount;

    void link(FibNode* y, FibNode* x);
    void consolidate();
    void cut(FibNode* x, FibNode* y);
    void cascadingCut(FibNode* y);

public:
    FibonacciHeap();

    void insertTask(const Task& t);
    Task extractHighestPriority();
    void decreaseTaskPriority(int id, int newPriority);
    bool isEmpty() const;
    void displayHeap() const;
    int size() const { return nodeCount; }
};

#endif //FIBONACCIHEAP_H



