#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include "storage.h"
#include <json.hpp>
#include <string>

class FileStorage : public IFileStorage {
private:
    std::string filename;

public:
    explicit FileStorage(const std::string& file);  
    //explicit stops the compiler from doing dumb implicit conversions(can lead to difficult to debug errors).
    // BAD: implicit conversion from const char* → std::string → FileStorage

    bool saveAll(const std::vector<Task>& tasks) override;
    bool loadAll(std::vector<Task>& tasks) override;
};

#endif
