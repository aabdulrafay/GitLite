# GitLite 🚀
### Advanced C++ CLI Version Control System

**GitLite** is a lightweight, fully functional version control system built from scratch in C++. It mimics the core architecture of Git, using a **content-addressable filesystem** to manage project history, snapshots, and file tracking.

This project demonstrates advanced **Operating Systems concepts**, including low-level file I/O, process management (fork/exec), Inter-Process Communication (IPC/Pipes), and custom memory caching.

---

## ⚡ Features

* **Repository Initialization:** Creates a hidden `.gitlite` object database.
* **Staging Area (Index):** Tracks files before committing using SHA-like hashing.
* **Snapshots:** Stores full file history, not just deltas.
* **Commit History:** Maintains a chronological log of changes with timestamps.
* **Time Travel:** `restore` files to their state in the previous commit.
* **Diff Engine:** Line-by-line comparison of working files vs. committed files.
* **Bulk Processing:** `bulk-add` feature to stage entire directories sequentially.
* **Performance:** Implements an **LRU Buffer Cache** to minimize disk reads.

---

## 🛠️ Build & Installation

### Prerequisites
* **OS:** Linux (Ubuntu/Debian recommended) or Windows (via MinGW/WSL).
* **Compiler:** `g++` (supporting C++17).
* **Make:** Standard GNU Make.

### Compilation
1.  **Clone or Extract** the project.
2.  **Clean** previous builds (optional but recommended):
    ```bash
    make clean
    ```
3.  **Compile** the source code:
    ```bash
    make
    ```
4.  **Verify** the executable:
    ```bash
    ./gitlite.sh
    ```
    *(If it says "Executable not found", run `make` again).*

---

## 📖 Usage Guide

Run all commands using the wrapper script `./gitlite.sh` or the built binary `./build/gitlite`.

| Command | Usage | Description |
| :--- | :--- | :--- |
| **Init** | `./gitlite.sh init` | Initialize a new repository. Creates `.gitlite/` folder. |
| **Add** | `./gitlite.sh add <file>` | Stage a specific file for the next commit. |
| **Bulk Add**| `./gitlite.sh bulk-add <dir>`| Stage all files in a directory at once. |
| **Status** | `./gitlite.sh status` | Show files currently staged in the Index. |
| **Commit** | `./gitlite.sh commit "<msg>"`| Save a snapshot of the staged files. |
| **Log** | `./gitlite.sh log` | View the history of commits (ID + Message). |
| **Diff** | `./gitlite.sh diff <file>` | Compare local file changes vs. last commit. |
| **Restore**| `./gitlite.sh restore <file>`| Revert a file to its last committed state. |

### Example Workflow
```bash
# 1. Setup
./gitlite.sh init

# 2. Create some work
echo "int main() { return 0; }" > main.cpp

# 3. Stage the file
./gitlite.sh add main.cpp

# 4. Save snapshot
./gitlite.sh commit "Initial commit"

# 5. Check history
./gitlite.sh log
