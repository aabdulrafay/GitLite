#include "commit.h"
#include "filesystem.h"
#include "hashing.h"
#include "diff.h"
#include "buffer_manager.h"
#include "thread_pool.h"
#include <iostream>
#include <filesystem>
#include <ctime>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

// Global constants for repository paths
string repo = ".gitlite";
string objects = ".gitlite/objects";
string commits = ".gitlite/commits";
string indexFile = ".gitlite/index";
string headFile = ".gitlite/HEAD";
string logFile = ".gitlite/log.txt";

// Helper function to get the current timestamp for commit ID
string timestamp() {
    time_t now = time(0);
    return to_string((long long)now);
}

void initRepo() {
    cout << "Setting up repository structure..." << endl;
    
    // 🚩 CRITICAL FIX: Must create the root directory (.gitlite) first!
    FileSystem::createDir(repo); 

    // Now create the subdirectories inside the established root
    FileSystem::createDir(objects);
    FileSystem::createDir(commits);
    
    // Now the files will be written successfully inside the existing .gitlite folder
    FileSystem::writeFile(indexFile, "");
    FileSystem::writeFile(headFile, "none");
    FileSystem::writeFile(logFile, "");
    
    cout << "✅ Repository initialized." << endl;
}

void addFile(const string &file) {
    if (!FileSystem::fileExists(file)) {
        cout << "❌ File not found: " << file << endl;
        return;
    }

    // Check buffer cache first
    string cachedHash = BufferManager::get(file);
    string hash;
    
    if (cachedHash.empty()) {
        string content = FileSystem::readFile(file);
        hash = simpleHash(content);
        
        // Write file content as an object in .gitlite/objects/
        FileSystem::writeFile(objects + "/" + hash, content);
        BufferManager::put(file, hash);
    } else {
        hash = cachedHash;
    }

    // Add file and hash to the staging index
    FileSystem::appendFile(indexFile, file + " " + hash + "\n");
    cout << "✅ Staged: " << file << " (hash: " << hash << ")" << endl;
}

void makeCommit(const string &msg) {
    string id = timestamp();
    
    // Create new commit directory
    FileSystem::createDir(commits + "/" + id);
    
    // Copy current staged index to the commit folder (snapshot)
    FileSystem::copyFile(indexFile, commits + "/" + id + "/index");
    
    // Write metadata
    FileSystem::writeFile(commits + "/" + id + "/message.txt", msg);
    FileSystem::writeFile(headFile, id);

    // Update log
    FileSystem::appendFile(logFile, id + " - " + msg + "\n");

    cout << "✅ Commit: " << id << endl;
    cout << "   Message: " << msg << endl;
}

void showLog() {
    string log = FileSystem::readFile(logFile);
    if (log.empty()) {
        cout << "📝 No commits yet." << endl;
    } else {
        cout << "📜 Commit History:\n" << log;
    }
}

void showStatus() {
    cout << "📊 --- Repository Status ---" << endl;
    
    cout << "\n📁 Staged Files (Index):\n";
    string index = FileSystem::readFile(indexFile);
    if (index.empty()) {
        cout << "   (none)" << endl;
    } else {
        cout << index;
    }

    cout << "\n🎯 Current HEAD: ";
    string head = FileSystem::readFile(headFile);
    cout << head << endl;
}

void restoreFile(const string &file) {
    string commitId = FileSystem::readFile(headFile);

    if (commitId == "none") {
        cout << "❌ No commits to restore from." << endl;
        return;
    }

    string indexPath = commits + "/" + commitId + "/index";
    if (!FileSystem::fileExists(indexPath)) {
        cout << "❌ Commit history structure error." << endl;
        return;
    }

    string index = FileSystem::readFile(indexPath);
    istringstream iss(index);
    string line, hash;

    // Search the index file for the target file's hash
    while (getline(iss, line)) {
        if (line.find(file) != string::npos) {
            size_t pos = line.find(" ");
            if (pos != string::npos) {
                hash = line.substr(pos + 1);
            }
            break;
        }
    }

    if (hash.empty()) {
        cout << "❌ File not found in last commit." << endl;
        return;
    }

    // Copy the object back to the working directory
    FileSystem::copyFile(objects + "/" + hash, file);
    cout << "✅ Restored: " << file << endl;
}

void diffFile(const string &file) {
    string commitId = FileSystem::readFile(headFile);
    
    if (commitId == "none") {
        cout << "❌ No commits to compare against." << endl;
        return;
    }

    string indexPath = commits + "/" + commitId + "/index";
    string index = FileSystem::readFile(indexPath);
    string hash;

    // Find the hash of the committed file
    istringstream iss(index);
    string line;
    while (getline(iss, line)) {
        if (line.find(file) != string::npos) {
            size_t pos = line.find(" ");
            if (pos != string::npos) {
                hash = line.substr(pos + 1);
            }
            break;
        }
    }

    if (hash.empty()) {
        cout << "❌ File not found in last commit." << endl;
        return;
    }

    string oldFile = objects + "/" + hash;
    // Call the diff logic
    runDiff(oldFile, file);
}

void parallelAdd(const string &directory) {
    if (!FileSystem::fileExists(directory)) {
        cout << "❌ Directory not found: " << directory << endl;
        return;
    }

    cout << "🚀 Starting parallel add operation..." << endl;
    
    // Create a Thread Pool with 4 worker threads
    ThreadPool pool(4); 
    vector<string> files = FileSystem::listFiles(directory);

    for (const string &file : files) {
        // Enqueue addFile task for each file
        pool.enqueue([file, directory]() {
            string fullPath = directory + "/" + file;
            addFile(fullPath);
        });
    }

    // Wait for all threads to complete their tasks
    pool.wait();
    cout << "✅ Parallel add completed!" << endl;
}
