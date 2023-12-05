#include "read_from_file.h"
#include <iostream>
#include <fstream>

using namespace std;

void readFromFile(string& filename) {
    string fullPath = "C:\\" + filename;
    ifstream inFile(fullPath);

    if (!inFile.is_open()) {
        cerr << "Не удалось открыть файл для чтения.\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        size_t lastNonSpace = line.find_last_not_of(" \t");
        if (lastNonSpace != string::npos) {
            line = line.substr(0, lastNonSpace + 1);
        }
        cout << line << endl;
    }

    inFile.close();
}