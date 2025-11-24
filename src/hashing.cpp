#include "hashing.h"
#include <sstream>
#include <iomanip>

std::string simpleHash(const std::string &data) {
    unsigned long hash = 5381;
    for (char c : data)
        hash = ((hash << 5) + hash) + c;
    return std::to_string(hash);
}

std::string sha256Hash(const std::string &data) {
    // Simplified hash for demonstration
    unsigned long hash = 0;
    for (size_t i = 0; i < data.length(); i++) {
        hash = data[i] + (hash << 6) + (hash << 16) - hash;
    }
    
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash;
    return ss.str();
}
