#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "task.h"

class IStorage {
public:
    virtual bool saveAll(const std::vector<Task>& tasks) = 0;
    virtual bool loadAll(std::vector<Task>& tasks) = 0;

    virtual ~IStorage() = default;
};

#endif
