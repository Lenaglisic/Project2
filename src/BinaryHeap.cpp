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
