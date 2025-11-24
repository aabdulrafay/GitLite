#include "filesystem.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <errno.h>

bool FileSystem::fileExists(const std::string &path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

std::string FileSystem::readFile(const std::string &path) {
    // Read operations should check for errors
    int fd = open(path.c_str(), O_RDONLY);
    if (fd < 0) {
        std::cerr << "❌ Read failed for " << path << ": " << strerror(errno) << std::endl;
        return "";
    }
    
    char buffer[4096];
    std::string content;
    ssize_t bytesRead;
    
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        content.append(buffer, bytesRead);
    }
    
    close(fd);
    return content;
}

void FileSystem::writeFile(const std::string &path, const std::string &data) {
    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        std::cerr << "❌ Write failed (open error): " << path << ": " << strerror(errno) << std::endl;
        return;
    }
    
    // Crucial fix: Check return value of write
    ssize_t bytesWritten = write(fd, data.c_str(), data.size());
    if (bytesWritten < 0) {
        std::cerr << "❌ Write failed (data error): " << path << ": " << strerror(errno) << std::endl;
    }
    
    close(fd);
}

void FileSystem::appendFile(const std::string &path, const std::string &data) {
    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        std::cerr << "❌ Append failed (open error): " << path << ": " << strerror(errno) << std::endl;
        return;
    }
    
    // Crucial fix: Check return value of write
    ssize_t bytesWritten = write(fd, data.c_str(), data.size());
    if (bytesWritten < 0) {
        std::cerr << "❌ Append failed (data error): " << path << ": " << strerror(errno) << std::endl;
    }
    
    close(fd);
}

void FileSystem::copyFile(const std::string &src, const std::string &dest) {
    std::string content = readFile(src);
    if (!content.empty() || fileExists(src)) { // Only write if read was successful or file exists and is empty
        writeFile(dest, content);
    } else {
        std::cerr << "❌ Copy failed: Source file " << src << " could not be read." << std::endl;
    }
}

void FileSystem::createDir(const std::string &path) {
    if (mkdir(path.c_str(), 0755) != 0) {
        // Ignore "File exists" error
        if (errno != EEXIST) { 
            std::cerr << "❌ Directory creation failed: " << path << ": " << strerror(errno) << std::endl;
        }
    }
}

std::vector<std::string> FileSystem::listFiles(const std::string &path) {
    std::vector<std::string> files;
    DIR *dir = opendir(path.c_str());
    
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_name[0] != '.') {
                files.push_back(entry->d_name);
            }
        }
        closedir(dir);
    } else {
        std::cerr << "❌ Cannot open directory: " << path << ": " << strerror(errno) << std::endl;
    }
    
    return files;
}

long FileSystem::getFileSize(const std::string &path) {
    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        return st.st_size;
    }
    return -1;
}

long FileSystem::getInode(const std::string &path) {
    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        return st.st_ino;
    }
    return -1;
}
