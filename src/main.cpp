#include <iostream>
#include "commit.h"
#include "ipc_handler.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Setup signal handlers
    IPCHandler::setupSignalHandlers();

    if (argc < 2) {
        cout << "Usage: gitlite <command> [args]" << endl;
        return 0;
    }

    string cmd = argv[1];

    if (cmd == "init") {
        initRepo();
    }
    else if (cmd == "add" && argc >= 3) {
        addFile(argv[2]);
    }
    else if (cmd == "commit" && argc >= 3) {
        makeCommit(argv[2]);
    }
    else if (cmd == "log") {
        showLog();
    }
    else if (cmd == "status") {
        showStatus();
    }
    else if (cmd == "restore" && argc >= 3) {
        restoreFile(argv[2]);
    }
    else if (cmd == "diff" && argc >= 3) {
        diffFile(argv[2]);
    }
    // Changed command logic
    else if (cmd == "bulk-add" && argc >= 3) {
        bulkAdd(argv[2]);
    }
    else {
        cout << "❌ Unknown command or missing arguments" << endl;
    }

    return 0;
}