#include <iostream>
#include <limits>

#include "task.h"
#include "file_storage.h"

int main() 
{
    FileStorage fs("tasks.txt");
    TaskManager tm(&fs);

    while (true) {
        std::cout << "\nOptions:\n---------\n";
        std::cout << "1. Add Task    2. List Tasks  3. Mark Done   4. Delete Task\n";
        std::cout << "5. Edit Task   6. Search      7. Sort        8. Exit\nEnter choice: ";
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
            case 5: tm.editTask(); break;
            case 6: tm.searchTasks(); break;
            case 7: tm.sortTasks(); break;
            case 8: std::cout << "Exiting...\n"; return 0;
            default: std::cout << "Invalid choice!\n";
        }
    }
    return 0;
}
