#include <iostream>
#include <limits>

#include "task.h"

int main() {
    TaskManager tm;
    while (true) {
        std::cout << "\n1. Add Task\n2. List Tasks\n3. Mark Done\n4. Delete Task\n5. Exit\nEnter choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // clear error flag detected by cin.fail()
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

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
