#include "diff.h"
#include "filesystem.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void runDiff(const string &oldFile, const string &newFile) {
    string oldContent = FileSystem::readFile(oldFile);
    string newContent = FileSystem::readFile(newFile);

    if (oldContent == newContent) {
        cout << "✅ No changes detected." << endl;
        return;
    }

    cout << "\n🔍 ---- DIFF OUTPUT ----" << endl;
    cout << "Old: " << oldFile << endl;
    cout << "New: " << newFile << endl;
    cout << "------------------------\n" << endl;

    stringstream oldStream(oldContent), newStream(newContent);
    string lineOld, lineNew;
    int lineNum = 1;

    vector<string> oldLines, newLines;
    while (getline(oldStream, lineOld)) oldLines.push_back(lineOld);
    while (getline(newStream, lineNew)) newLines.push_back(lineNew);

    size_t maxLines = max(oldLines.size(), newLines.size());

    for (size_t i = 0; i < maxLines; i++) {
        if (i < oldLines.size() && i < newLines.size()) {
            if (oldLines[i] != newLines[i]) {
                cout << "Line " << (i + 1) << ":" << endl;
                cout << "  - " << oldLines[i] << endl;
                cout << "  + " << newLines[i] << endl;
            }
        } else if (i < oldLines.size()) {
            cout << "Line " << (i + 1) << " (deleted):" << endl;
            cout << "  - " << oldLines[i] << endl;
        } else {
            cout << "Line " << (i + 1) << " (added):" << endl;
            cout << "  + " << newLines[i] << endl;
        }
    }
}
