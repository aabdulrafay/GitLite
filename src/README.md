# GitLite - Advanced Operating System Project

## 🎯 OS Concepts Implemented

1. **Process Management** - Fork, Exec, Wait
2. **Inter-Process Communication** - Pipes
3. **Signal Handling** - SIGINT, SIGTERM
4. **Multi-threading** - Thread Pool
5. **Memory Management** - Buffer Cache
6. **File System** - Low-level system calls

## 🚀 Setup & Compilation

### Prerequisites
- g++ compiler (C++17 support)
- Linux/Unix environment
- pthread library

### Build
```bash
make
```

### Clean
```bash
make clean
```

## 📖 Usage

### Initialize Repository
```bash
./gitlite.sh init
```

### Add Files
```bash
./gitlite.sh add file.txt
```

### Commit Changes
```bash
./gitlite.sh commit "Your message"
```

### View Log
```bash
./gitlite.sh log
```

### Check Status
```bash
./gitlite.sh status
```

### View Differences
```bash
./gitlite.sh diff file.txt
```

### Restore File
```bash
./gitlite.sh restore file.txt
```

### Parallel Add (OS Feature)
```bash
./gitlite.sh parallel-add ./src/
```

## 👥 Team Members

- **Member 1**: Process & IPC modules
- **Member 2**: Threading & Memory management
- **Member 3**: Core Git operations

## 📊 Project Statistics

- Lines of Code: ~1000+
- Files: 19
- OS Concepts: 7
- Advanced Features: 5

## 🎓 Academic Information

**Course**: Operating Systems  
**Project**: Version Control System with OS Concepts  
**Level**: Advanced  
**Team Size**: 3 members
