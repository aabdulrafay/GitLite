#ifndef IPC_HANDLER_H
#define IPC_HANDLER_H

#include <string>

class IPCHandler {
public:
    static void sendViaPipe(const std::string &message);
    static std::string receiveViaPipe();
    static void setupSignalHandlers();
};

#endif
