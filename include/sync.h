#ifndef SYNC_H
#define SYNC_H

#include <string>

class Sync {
public:
    static void upload(const std::string& filePath);
    static void download();
};

#endif
