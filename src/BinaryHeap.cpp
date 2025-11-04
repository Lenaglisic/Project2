//
// 
//
#include "BinaryHeap.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Task {
    int id;
    string name;
    int priority;
    Task(int i, string n, int p) {
        int id = i;
        string name = n;
        int priority = p;
    }
};

bool operator>(const Task& a, const Task& b) {
    return a.priority > b.priority;
}

class BinaryHeap {
private:
    vector<Task> heap;
    int parent(int i) {
        return (i - 1) / 2;
    }
    int left(int i) {
        return 2 * i + 1;
    }
    int right(int i) {
        return 2 * i + 2;
    }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int size = heap.size();
        int largest = i;
        int l = left(i);
        int r = right(i);
        if (l < size && heap[l] > heap[largest]) {
            largest = l;
        }
        if (r < size && heap[r] > heap[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(Task t) {
        heap.push_back(t);
        heapifyUp(heap.size() - 1);
    }
    Task getTop() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }
    void pop() {
        if (heap.empty()){
            throw runtime_error("Heap is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }
};
