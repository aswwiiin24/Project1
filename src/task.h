#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

struct Task {
    int id;
    std::string title;
    bool completed;
};

class TaskManager {
private:
    std::vector<Task> tasks;
    const std::string filename = "tasks.txt";

    void saveTasks() const;
    void loadTasks();

public:
    TaskManager();
    void addTask();
    void listTasks() const;
    void markDone();
    void deleteTask();
};

#endif
