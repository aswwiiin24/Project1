#include "task.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>


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
        file << t.id << "|" 
             << t.title << "|" 
             << (t.completed ? 1 : 0) << "|" 
             << t.priority << "|" 
             << t.createdTime << "|" 
             << t.dueDate << "\n";
    }
}

void TaskManager::loadTasks() {
    tasks.clear();
    std::ifstream file(filename);
    if (!file) return; // no file yet

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string idStr, title, compStr, priStr, created, due;

        // now we expect 6 fields
        if (std::getline(ss, idStr, '|') &&
            std::getline(ss, title, '|') &&
            std::getline(ss, compStr, '|') &&
            std::getline(ss, priStr, '|') &&
            std::getline(ss, created, '|') &&
            std::getline(ss, due)) {

            Task t;
            t.id = std::stoi(idStr);
            t.title = title;
            t.completed = (compStr == "1");
            t.priority = std::stoi(priStr);
            t.createdTime = created;
            t.dueDate = due;

            tasks.push_back(t);
        }
    }
}

void TaskManager::addTask() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
    std::string title;
    std::cout << "Enter task title: ";
    std::getline(std::cin, title);

    bool valid = false;
    for (char c : title) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            valid = true;
            break;
        }
    }

    if (!valid) {
        std::cout << "Task title cannot be empty. Please try again.\n";
        return;
    }

    Task t;
    t.id = tasks.empty() ? 1 : tasks.back().id + 1;
    t.title = title;
    t.completed = false;

    t.createdTime = getCurrentTime();

    std::cout << "Enter priority (1=Low, 2=Medium, 3=High): ";
    std::cin >> t.priority;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter due date (optional, format YYYY-MM-DD, press Enter to skip): ";
    std::getline(std::cin, t.dueDate);
    if (t.dueDate.empty()) t.dueDate = "N/A";

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
          << " [Priority: " << t.priority << "] "
          << "[Created: " << t.createdTime << "] "
          << "[Due: " << t.dueDate << "] "
          << "[" << (t.completed ? "Done" : "Pending") << "]\n";
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

void TaskManager::editTask() {
    if (tasks.empty()) {
        std::cout << "No tasks to edit.\n";
        return;
    }

    std::cout << "Enter task ID to edit: ";
    int id;
    std::cin >> id;

    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [id](const Task &t){ return t.id == id; });

    if (it == tasks.end()) {
        std::cout << "Invalid ID.\n";
        return;
    }

    Task &t = *it;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Current Title: " << t.title << "\nEnter new title (press Enter to keep same): ";
    std::string newTitle;
    std::getline(std::cin, newTitle);
    if (!newTitle.empty()) t.title = newTitle;

    std::cout << "Current Priority: " << t.priority << "\nEnter new priority (1=Low, 2=Medium, 3=High, 0=keep same): ";
    int newPriority;
    std::cin >> newPriority;
    if (newPriority >= 1 && newPriority <= 3) t.priority = newPriority;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Current Due Date: " << t.dueDate << "\nEnter new due date (YYYY-MM-DD or Enter to keep same): ";
    std::string newDue;
    std::getline(std::cin, newDue);
    if (!newDue.empty()) t.dueDate = newDue;

    saveTasks();
    std::cout << "Task updated successfully.\n";
}

void TaskManager::searchTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks available.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter keyword to search (or type 'done' / 'pending' to filter by status): ";
    std::string query;
    std::getline(std::cin, query);

    bool found = false;
    std::cout << "\n--- Search Results ---\n";

    for (const auto &t : tasks) {
        bool match = false;

        // Case-insensitive match for title
        std::string titleLower = t.title;
        std::string queryLower = query;
        std::transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
        std::transform(queryLower.begin(), queryLower.end(), queryLower.begin(), ::tolower);

        if (titleLower.find(queryLower) != std::string::npos) match = true;

        if (queryLower == "done" && t.completed) match = true;
        if (queryLower == "pending" && !t.completed) match = true;

        if (match) {
            found = true;
            std::cout << t.id << ". " << t.title
                      << " [Priority: " << t.priority << "] "
                      << "[" << (t.completed ? "Done" : "Pending") << "]\n";
        }
    }

    if (!found) std::cout << "No matching tasks found.\n";
}

void TaskManager::sortTasks() {
    if (tasks.empty()) {
        std::cout << "No tasks to sort.\n";
        return;
    }

    std::sort(tasks.begin(), tasks.end(),
              [](const Task &a, const Task &b) {
                  // Pending tasks first, then completed
                  if (a.completed != b.completed)
                      return !a.completed && b.completed;
                  // If same status, sort by priority (High > Low)
                  return a.priority > b.priority;
              });

    // Reassign IDs after sorting
    for (size_t i = 0; i < tasks.size(); ++i)
        tasks[i].id = static_cast<int>(i + 1);

    saveTasks();
    std::cout << "Tasks sorted by completion and priority.\n";
}

