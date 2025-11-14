#include "file_storage.h"
#include <fstream>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

FileStorage::FileStorage(const std::string& file)
    : filename(file) {}

// Save tasks to file
bool FileStorage::saveAll(const std::vector<Task>& tasks) {
    json j_tasks = json::array();

    for (const auto& t : tasks) {
        j_tasks.push_back({
            {"id", t.id},
            {"title", t.title},
            {"completed", t.completed},
            {"priority", t.priority},
            {"createdTime", t.createdTime},
            {"dueDate", t.dueDate}
        });
    }

    std::ofstream file(filename);
    if (!file) return false;

    file << j_tasks.dump(4); // pretty print
    return true;
}


// Load tasks from file
bool FileStorage::loadAll(std::vector<Task>& tasks) {
    tasks.clear();

    std::ifstream file(filename);
    if (!file) return true;   // no file = no error

    json j_tasks;
    file >> j_tasks;

    for (const auto& j : j_tasks) {
        Task t;
        t.id = j.value("id", 0);
        t.title = j.value("title", "");
        t.completed = j.value("completed", false);
        t.priority = j.value("priority", 1);
        t.createdTime = j.value("createdTime", "N/A");
        t.dueDate = j.value("dueDate", "N/A");
        tasks.push_back(t);
    }

    return true;
}

