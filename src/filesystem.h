#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>

class FileSystem {
public:
    static bool fileExists(const std::string &path);
    static std::string readFile(const std::string &path);
    static void writeFile(const std::string &path, const std::string &data);
    static void appendFile(const std::string &path, const std::string &data);
    static void copyFile(const std::string &src, const std::string &dest);
    static void createDir(const std::string &path);
    static std::vector<std::string> listFiles(const std::string &path);
    static long getFileSize(const std::string &path);
    static long getInode(const std::string &path);
};

#endif
