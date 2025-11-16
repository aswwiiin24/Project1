#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "task.h"

class IFileStorage {
public:
    virtual bool saveAll(const std::vector<Task>& tasks) = 0;
    virtual bool loadAll(std::vector<Task>& tasks) = 0;

    virtual ~IFileStorage() = default;
};

#endif
