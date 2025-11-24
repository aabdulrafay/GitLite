#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <string>
#include <vector>

class ProcessManager {
public:
    static int executeCommand(const std::string &cmd);
    static void forkAndExecute(const std::string &cmd);
    static void waitForChildren();
    static std::vector<int> childPids;
};

#endif
