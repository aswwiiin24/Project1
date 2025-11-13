#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include "utils.h"

struct Task {
    int id;
    std::string title;
    bool completed;
    int priority;                     // 1 = Low, 2 = Medium, 3 = High
    std::string createdTime;          // auto-generated timestamp
    std::string dueDate;              // optional, can be empty
};

class TaskManager {
private:
    std::vector<Task> tasks;
    const std::string filename = "tasks.txt";

    void saveTasks() const; //const to ensure it doesn't modify member variables
    void loadTasks();

public:
    TaskManager();
    void addTask();
    void listTasks() const;
    void markDone();
    void deleteTask();
    void editTask();
    void searchTasks() const;
    void sortTasks();
};

#endif
