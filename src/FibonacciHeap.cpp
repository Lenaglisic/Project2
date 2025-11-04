//
// Created by Lena Glisic on 11/3/25.
//
#include "FibonacciHeap.h"
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

struct Task {
    int id;
    string name;
    int priority;
    Task(int i, string n, int p) : id(i), name(n), priority(p) {}
};

bool operator>(const Task& a, const Task& b) {
    return a.priority > b.priority;
}

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
        Node(Task t) : task(t), parent(nullptr), child(nullptr),
                       left(this), right(this), degree(0), mark(false) {}
    };

    Node* minNode;
    int nodeCount;

    void link(Node* y, Node* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        if (!x->child) x->child = y;
        else {
            y->right = x->child->right;
            y->left = x->child;
            x->child->right->left = y;
            x->child->right = y;
        }
        x->degree++;
        y->mark = false;
    }

    void consolidate() {
        int D = log2(nodeCount) + 2;
        vector<Node*> A(D, nullptr);
        vector<Node*> roots;
        Node* curr = minNode;
        if (!curr) return;
        do { roots.push_back(curr); curr = curr->right; } while (curr != minNode);
        for (auto w : roots) {
            Node* x = w;
            int d = x->degree;
            while (A[d]) {
                Node* y = A[d];
                if (y->task.priority < x->task.priority) swap(x, y);
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }
        minNode = nullptr;
        for (auto a : A) {
            if (a) {
                if (!minNode) minNode = a, a->left = a->right = a;
                else {
                    a->left = minNode;
                    a->right = minNode->right;
                    minNode->right->left = a;
                    minNode->right = a;
                    if (a->task.priority < minNode->task.priority) minNode = a;
                }
            }
        }
    }

public:
    FibonacciHeap() : minNode(nullptr), nodeCount(0) {}

    void insert(Task t) {
        Node* n = new Node(t);
        if (!minNode) minNode = n;
        else {
            n->left = minNode;
            n->right = minNode->right;
            minNode->right->left = n;
            minNode->right = n;
            if (t.priority < minNode->task.priority) minNode = n;
        }
        nodeCount++;
    }

    Task getTop() {
        if (!minNode) throw runtime_error("Heap empty");
        return minNode->task;
    }

    void pop() {
        if (!minNode) throw runtime_error("Heap empty");
        Node* z = minNode;
        if (z->child) {
            Node* c = z->child;
            do { c->parent = nullptr; c = c->right; } while (c != z->child);
            Node* minLeft = z->left;
            Node* childLeft = z->child->left;
            minLeft->right = z->child;
            z->child->left = minLeft;
            childLeft->right = z->right;
            z->right->left = childLeft;
        }
        z->left->right = z->right;
        z->right->left = z->left;
        if (z == z->right) minNode = nullptr;
        else { minNode = z->right; consolidate(); }
        delete z;
        nodeCount--;
    }

    bool isEmpty() const { return minNode == nullptr; }

    void displayHeap() {
        if (!minNode) { cout << "Heap is empty\n"; return; }
        Node* curr = minNode;
        cout << "Root nodes:\n";
        do {
            cout << "ID=" << curr->task.id << " P=" << curr->task.priority
                 << " Name=" << curr->task.name << endl;
            curr = curr->right;
        } while (curr != minNode);
    }
};
