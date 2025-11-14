#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include "storage.h"
#include <string>

class FileStorage : public IStorage {
private:
    std::string filename;

public:
    explicit FileStorage(const std::string& file);

    bool saveAll(const std::vector<Task>& tasks) override;
    bool loadAll(std::vector<Task>& tasks) override;
};

#endif
