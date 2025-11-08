#include "BinaryHeap.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


void BinaryHeap::heapifyUp(int i) {
    while (i > 0)
    {
        int p = parent(i);
        if (heap[p].priority <= heap[i].priority) break;
        swap(heap[i], heap[p]);
        i = p;
    }
}

void BinaryHeap::heapifyDown(int i) {
    int size = heap.size();
    int smallest = i;
    int l = left(i);
    int r = right(i);
    if (l < size && heap[l].priority < heap[smallest].priority) {
        smallest = l;
    }
    if (r < size && heap[r].priority < heap[smallest].priority) {
        smallest = r;
    }
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}


void BinaryHeap::insert(const Task& t) {
    heap.push_back(t);
    heapifyUp(heap.size() - 1);
}

Task BinaryHeap::getTop() const{
    if (heap.empty()) {
        throw runtime_error("Heap is empty");
    }
    return heap[0];
}

void BinaryHeap::pop() {
    if (heap.empty()){
        throw runtime_error("Heap is empty");
    }
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
}

const Task* BinaryHeap::findById(int id) const
{
    for (const auto& t : heap)
    {
        if (t.id == id) return &t;

    }
    return nullptr;
}
