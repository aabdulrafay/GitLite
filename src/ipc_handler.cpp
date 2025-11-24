#include "ipc_handler.h"
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <cstring>
#include <errno.h>

int pipeFds[2];

void IPCHandler::sendViaPipe(const std::string &message) {
    if (pipe(pipeFds) == -1) {
        std::cerr << "❌ Pipe creation failed: " << strerror(errno) << std::endl;
        return;
    }
    
    // Crucial fix: Check return value of write
    ssize_t bytesWritten = write(pipeFds[1], message.c_str(), message.size());
    if (bytesWritten < 0) {
        std::cerr << "❌ Pipe write failed: " << strerror(errno) << std::endl;
    }

    close(pipeFds[1]);
    std::cout << "📤 Sent via pipe: " << message << std::endl;
}

std::string IPCHandler::receiveViaPipe() {
    char buffer[1024];
    ssize_t bytesRead = read(pipeFds[0], buffer, sizeof(buffer) - 1);
    close(pipeFds[0]);
    
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "📥 Received via pipe: " << buffer << std::endl;
        return std::string(buffer);
    }
    return "";
}

void signalHandler(int signum) {
    std::cout << "\n🛑 Interrupt signal (" << signum << ") received." << std::endl;
    exit(signum);
}

void IPCHandler::setupSignalHandlers() {
    // Check if signal setting was successful
    if (signal(SIGINT, signalHandler) == SIG_ERR) {
        std::cerr << "❌ Cannot catch SIGINT" << std::endl;
    }
    if (signal(SIGTERM, signalHandler) == SIG_ERR) {
        std::cerr << "❌ Cannot catch SIGTERM" << std::endl;
    }
}
