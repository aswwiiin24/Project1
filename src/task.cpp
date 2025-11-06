#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "task.h"

Task tasks[MAX_TASKS];
int taskCount = 0;

static void read_line(char *buf, size_t size) {
    if (fgets(buf, (int)size, stdin)) {
        buf[strcspn(buf, "\n")] = 0;
    } else {
        buf[0] = 0;
    }
}

void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task list full!\n");
        return;
    }
    char title[100];
    printf("Enter task title: ");
    read_line(title, sizeof(title));
    strncpy(tasks[taskCount].title, title, sizeof(tasks[taskCount].title));
    tasks[taskCount].title[sizeof(tasks[taskCount].title) - 1] = 0;
    tasks[taskCount].id = taskCount + 1;
    tasks[taskCount].completed = 0;
    taskCount++;
    printf("Task added successfully!\n");
}

void listTasks() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }
    printf("\n--- Task List ---\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s [%s]\n", tasks[i].id, tasks[i].title,
               tasks[i].completed ? "Done" : "Pending");
    }
}

void markDone() {
    char buf[32];
    printf("Enter task ID to mark done: ");
    read_line(buf, sizeof(buf));
    int id = atoi(buf);
    if (id < 1 || id > taskCount) {
        printf("Invalid ID.\n");
        return;
    }
    tasks[id - 1].completed = 1;
    printf("Task marked as done.\n");
}

void deleteTask() {
    char buf[32];
    printf("Enter task ID to delete: ");
    read_line(buf, sizeof(buf));
    int id = atoi(buf);
    if (id < 1 || id > taskCount) {
        printf("Invalid ID.\n");
        return;
    }
    for (int i = id - 1; i < taskCount - 1; i++)
        tasks[i] = tasks[i + 1];
    taskCount--;
    for (int i = 0; i < taskCount; i++)
        tasks[i].id = i + 1;
    printf("Task deleted.\n");
}