//
// Created by Lena Glisic on 11/3/25.
//

#include "FibonacciHeap.h"
#include <limits>
#include <queue>
#include <unordered_map>
#include <iomanip>
#include <unordered_set>
#include <utility>

// Constructor
FibonacciHeap::FibonacciHeap() {
    minNode = nullptr;
    nodeCount = 0;
}

// Helper Functions

// Link two trees of the same degree
void FibonacciHeap::link(FibNode* y, FibNode* x) {
    // Remove y from root list
    y->left->right = y->right;
    y->right->left = y->left;

    // Make y a child of x
    y->parent = x;
    if (x->child == nullptr) {
        x->child = y;
        y->left = y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }

    x->degree++;
    y->mark = false;
}

// Consolidate the heap
void FibonacciHeap::consolidate() {
    int D = static_cast<int>(std::log2(nodeCount)) + 1;
    std::vector<FibNode*> A(D, nullptr);

    // Root list traversal
    std::vector<FibNode*> roots;
    FibNode* curr = minNode;
    if (curr != nullptr) {
        do {
            roots.push_back(curr);
            curr = curr->right;
        } while (curr != minNode);
    }

    for (auto w : roots) {
        FibNode* x = w;
        int d = x->degree;
        while (A[d] != nullptr) {
            FibNode* y = A[d];
            if (y->task.priority < x->task.priority) std::swap(x, y);
            link(y, x);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
    }

    minNode = nullptr;
    for (auto a : A) {
        if (a != nullptr) {
            if (minNode == nullptr) {
                minNode = a;
                a->left = a->right = a;
            } else {
                a->left = minNode;
                a->right = minNode->right;
                minNode->right->left = a;
                minNode->right = a;
                if (a->task.priority < minNode->task.priority)
                    minNode = a;
            }
        }
    }
}

// Cut node from parent
void FibonacciHeap::cut(FibNode* x, FibNode* y) {
    if (x->right == x)
        y->child = nullptr;
    else {
        x->left->right = x->right;
        x->right->left = x->left;
        if (y->child == x)
            y->child = x->right;
    }

    y->degree--;

    // Add x to root list
    x->left = minNode;
    x->right = minNode->right;
    minNode->right->left = x;
    minNode->right = x;
    x->parent = nullptr;
    x->mark = false;
}

// Cascading cut
void FibonacciHeap::cascadingCut(FibNode* y) {
    FibNode* z = y->parent;
    if (z != nullptr) {
        if (!y->mark)
            y->mark = true;
        else {
            cut(y, z);
            cascadingCut(z);
        }
    }
}

// Core Operations

// Insert a new task into the heap
void FibonacciHeap::insertTask(const Task& t) {
    auto* newNode = new FibNode(t);

    if (minNode == nullptr) {
        minNode = newNode;
    } else {
        // Insert into root list
        newNode->left = minNode;
        newNode->right = minNode->right;
        minNode->right->left = newNode;
        minNode->right = newNode;
        if (t.priority < minNode->task.priority)
            minNode = newNode;
    }

    nodeCount++;
}

// Extract highest-priority (lowest value) task
Task FibonacciHeap::extractHighestPriority() {
    if (minNode == nullptr)
        throw std::runtime_error("Heap is empty!");

    FibNode* z = minNode;

    // Move z's children to the root list
    if (z->child != nullptr) {
        FibNode* c = z->child;
        do {
            c->parent = nullptr;
            c = c->right;
        } while (c != z->child);

        // Merge with root list
        FibNode* minLeft = minNode->left;
        FibNode* childLeft = z->child->left;
        minLeft->right = z->child;
        z->child->left = minLeft;
        childLeft->right = minNode;
        minNode->left = childLeft;
    }

    // Remove z from the root list
    z->left->right = z->right;
    z->right->left = z->left;

    if (z == z->right)
        minNode = nullptr;
    else {
        minNode = z->right;
        consolidate();
    }

    nodeCount--;
    Task result = z->task;
    delete z;
    return result;
}

// Decrease task priority
void FibonacciHeap::decreaseTaskPriority(int id, int newPriority) {
    if (minNode == nullptr) return;

    std::queue<FibNode*> q;
    q.push(minNode);
    FibNode* target = nullptr;

    while (!q.empty()) {
        FibNode* n = q.front(); q.pop();
        FibNode* start = n;
        do {
            if (n->task.id == id) {
                target = n;
                break;
            }
            if (n->child != nullptr)
                q.push(n->child);
            n = n->right;
        } while (n != start);
        if (target) break;
    }

    if (target != nullptr && newPriority < target->task.priority) {
        target->task.priority = newPriority;
        FibNode* y = target->parent;
        if (y != nullptr && target->task.priority < y->task.priority) {
            cut(target, y);
            cascadingCut(y);
        }
        if (target->task.priority < minNode->task.priority)
            minNode = target;
    }
}

// Check if empty
bool FibonacciHeap::isEmpty() const {
    return minNode == nullptr;
}

// Display heap (for debugging)
void FibonacciHeap::displayHeap() const {
    if (minNode == nullptr) {
        std::cout << "Heap is empty.\n";
        return;
    }

    std::cout << "Root nodes:\n";
    FibNode* curr = minNode;
    do {
        std::cout << "Task " << curr->task.id
                  << " | Priority: " << curr->task.priority
                  << " | Name: " << curr->task.name << "\n";
        curr = curr->right;
    } while (curr != minNode);
}

const Task* FibonacciHeap::findById(int id) const
{
    if (minNode == nullptr) return nullptr;

    std::queue<FibNode*> q;
    std::unordered_set<FibNode*> visited;
    q.push(minNode);

    while (!q.empty()) {
        FibNode* n = q.front(); q.pop();
        if (visited.count(n)) continue;
        visited.insert(n);

        FibNode* start = n;
        bool first = true;
        while (first || n!= start)
        {
            first = false;
            if (n->task.id == id) return &n->task;
            if (n->child) q.push(n->child);

            n = n->right;
        }
    }
    return nullptr;
}
