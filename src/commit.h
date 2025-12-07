#ifndef COMMIT_H
#define COMMIT_H

#include <string>

void initRepo();
void addFile(const std::string &file);
void makeCommit(const std::string &msg);
void showLog();
void showStatus();
void restoreFile(const std::string &file);
void diffFile(const std::string &file);
void bulkAdd(const std::string &directory); // Renamed from parallelAdd

#endif