#include <stdio.h>
#include <stdlib.h>
#include "task.h"

int main() {
    char buf[16];
    while (1) {
        printf("\n1. Add Task\n2. List Tasks\n3. Mark Done\n4. Delete Task\n5. Exit\nEnter choice: ");
        if (scanf("%15s", buf) != 1) break;
        int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
        int choice = atoi(buf);
        switch (choice) {
            case 1: addTask(); break;
            case 2: listTasks(); break;
            case 3: markDone(); break;
            case 4: deleteTask(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}