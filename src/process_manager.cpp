#include "process_manager.h"
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

std::vector<int> ProcessManager::childPids;

int ProcessManager::executeCommand(const std::string &cmd) {
    return system(cmd.c_str());
}

void ProcessManager::forkAndExecute(const std::string &cmd) {
    pid_t pid = fork();
    
    if (pid < 0) {
        std::cerr << "❌ Fork failed" << std::endl;
        return;
    }
    
    if (pid == 0) {
        // Child process
        execlp("/bin/sh", "sh", "-c", cmd.c_str(), nullptr);
        exit(1);
    } else {
        // Parent process
        childPids.push_back(pid);
        std::cout << "✅ Spawned process: " << pid << std::endl;
    }
}

void ProcessManager::waitForChildren() {
    for (int pid : childPids) {
        int status;
        waitpid(pid, &status, 0);
        std::cout << "✅ Process " << pid << " completed" << std::endl;
    }
    childPids.clear();
}
