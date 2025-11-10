#include <iostream>
#include "task.h"

int main() {
    TaskManager tm;
    while (true) {
        std::cout << "\n1. Add Task\n2. List Tasks\n3. Mark Done\n4. Delete Task\n5. Exit\nEnter choice: ";

        int choice;
        if (!(std::cin >> choice)) break;

        switch (choice) {
            case 1: tm.addTask(); break;
            case 2: tm.listTasks(); break;
            case 3: tm.markDone(); break;
            case 4: tm.deleteTask(); break;
            case 5: std::cout << "Exiting...\n"; return 0;
            default: std::cout << "Invalid choice!\n";
        }
    }
    return 0;
}
