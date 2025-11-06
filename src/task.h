#ifndef TASK_H
#define TASK_H

#define MAX_TASKS 100

struct Task {
    int id;
    char title[100];
    int completed; // 0 = not done, 1 = done
};

extern Task tasks[MAX_TASKS];
extern int taskCount;

void addTask();
void listTasks();
void markDone();
void deleteTask();

#endif 