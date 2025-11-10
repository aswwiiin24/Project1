#include "task.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

TaskManager::TaskManager() {
    loadTasks();
}

void TaskManager::saveTasks() const {
    std::ofstream file(filename, std::ios::trunc);
    if (!file) {
        std::cerr << "Error: Unable to save tasks.\n";
        return;
    }
    for (const auto &t : tasks) {
        file << t.id << "|" << t.title << "|" << (t.completed ? 1 : 0) << "\n";
    }
}

void TaskManager::loadTasks() {
    tasks.clear();
    std::ifstream file(filename);
    if (!file) return; // no file yet, skip

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string idStr, title, compStr;

        if (std::getline(ss, idStr, '|') && std::getline(ss, title, '|') && std::getline(ss, compStr)) {
            Task t;
            t.id = std::stoi(idStr);
            t.title = title;
            t.completed = (compStr == "1");
            tasks.push_back(t);
        }
    }
}

void TaskManager::addTask() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
    std::string title;
    std::cout << "Enter task title: ";
    std::getline(std::cin, title);

    Task t;
    t.id = tasks.empty() ? 1 : tasks.back().id + 1;
    t.title = title;
    t.completed = false;

    tasks.push_back(t);
    saveTasks();

    std::cout << "Task added successfully!\n";
}

void TaskManager::listTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks available.\n";
        return;
    }

    std::cout << "\n--- Task List ---\n";
    for (const auto &t : tasks) {
        std::cout << t.id << ". " << t.title
                  << " [" << (t.completed ? "Done" : "Pending") << "]\n";
    }
}

void TaskManager::markDone() {
    std::cout << "Enter task ID to mark done: ";
    int id;
    std::cin >> id;

    for (auto &t : tasks) {
        if (t.id == id) {
            t.completed = true;
            saveTasks();
            std::cout << "Task marked as done.\n";
            return;
        }
    }
    std::cout << "Invalid ID.\n";
}

void TaskManager::deleteTask() {
    std::cout << "Enter task ID to delete: ";
    int id;
    std::cin >> id;

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            // Reassign IDs
            for (size_t i = 0; i < tasks.size(); ++i)
                tasks[i].id = static_cast<int>(i + 1);
            saveTasks();
            std::cout << "Task deleted.\n";
            return;
        }
    }
    std::cout << "Invalid ID.\n";
}
