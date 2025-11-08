#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "Task.h"
#include <vector>
#include <stdexcept>

class BinaryHeap {
public:
    void insert(const Task& t);
    Task getTop() const;
    void pop();
    const Task* findById(int id) const;

    bool empty() const {return heap.empty();}
    size_t size() const {return heap.size();}

private:
    std::vector<Task> heap;

    static int parent(int i) {return (i - 1) / 2;}
    static int left(int i)   {return 2 * i + 1;}
    static int right(int i)  {return 2 * i + 2;}

    void heapifyUp(int i);
    void heapifyDown(int i);
};

#endif // BINARY_HEAP_H
