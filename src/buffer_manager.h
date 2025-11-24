#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include <string>
#include <unordered_map>
#include <mutex>

class BufferManager {
private:
    static std::unordered_map<std::string, std::string> cache;
    static std::mutex cacheMutex;
    static const size_t MAX_CACHE_SIZE = 100;

public:
    static void put(const std::string &key, const std::string &value);
    static std::string get(const std::string &key);
    static void clear();
    static bool exists(const std::string &key);
};

#endif
