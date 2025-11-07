#include <string>
#ifndef TASK_H
#define TASK_H

struct Task {
    int id;
    std::string name;
    int priority;
    Task(int i, std::string n, int p) {
        this->id = i;
        this->name = n;
        this->priority = p;
    }
};

#endif //TASK_H
