//
// Created by Lena Glisic on 11/3/25.
//

#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Task {
    int id;
    string name;
    int priority;
    Task(int i, string n, int p);
};

class FibonacciHeap {
private:
    struct Node {
        Task task;
        Node* parent;
        Node* child;
        Node* left;
        Node* right;
        int degree;
        bool mark;
        Node(Task t);
    };

    Node* minNode;
    int nodeCount;

    void link(Node* y, Node* x);
    void consolidate();

public:
    FibonacciHeap();

    void insert(Task t);
    Task getTop();
    void pop();
    bool isEmpty() const;
    void displayHeap();
};

#endif // FIBONACCIHEAP_H
