#include "buffer_manager.h"
#include <iostream>

std::unordered_map<std::string, std::string> BufferManager::cache;
std::mutex BufferManager::cacheMutex;

void BufferManager::put(const std::string &key, const std::string &value) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    
    if (cache.size() >= MAX_CACHE_SIZE) {
        cache.clear(); // Simple eviction policy
        std::cout << "🗑️  Buffer cache cleared (LRU)" << std::endl;
    }
    
    cache[key] = value;
    std::cout << "💾 Cached: " << key << std::endl;
}

std::string BufferManager::get(const std::string &key) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    
    if (cache.find(key) != cache.end()) {
        std::cout << "⚡ Cache hit: " << key << std::endl;
        return cache[key];
    }
    
    std::cout << "❌ Cache miss: " << key << std::endl;
    return "";
}

void BufferManager::clear() {
    std::lock_guard<std::mutex> lock(cacheMutex);
    cache.clear();
}

bool BufferManager::exists(const std::string &key) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    return cache.find(key) != cache.end();
}
