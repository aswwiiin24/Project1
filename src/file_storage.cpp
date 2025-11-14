#include "file_storage.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileStorage::FileStorage(const std::string& file)
    : filename(file) {}

// Save tasks to file
bool FileStorage::saveAll(const std::vector<Task>& tasks) {
    std::ofstream file(filename, std::ios::trunc);
    if (!file) {
        std::cerr << "Error: Unable to open file for saving.\n";
        return false;
    }

    for (const auto& t : tasks) {
        file << t.id << "|" 
             << t.title << "|" 
             << (t.completed ? 1 : 0) 
             << "\n";
    }

    return true;
}

// Load tasks from file
bool FileStorage::loadAll(std::vector<Task>& tasks) {
    tasks.clear();

    std::ifstream file(filename);
    if (!file) {
        // no file yet, not an error
        return true;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);

        std::string idStr, title, compStr;
        if (std::getline(ss, idStr, '|') &&
            std::getline(ss, title, '|') &&
            std::getline(ss, compStr)) 
        {
            Task t;
            t.id = std::stoi(idStr);
            t.title = title;
            t.completed = (compStr == "1");
            tasks.push_back(t);
        }
    }

    return true;
}
