#include "open_file.h"
#include <iostream>
#include <fstream>

using namespace std;

void openFile(string& filename) {
    cout << "Введите имя файла: ";
    cin.ignore();
    getline(cin, filename);
    string fullPath = "C:\\" + filename;

    ifstream outFile(fullPath, ios::binary);
    if (outFile.is_open()) {
        cout << "Файл '" << filename << "' успешно открыт.\n";
        outFile.close();

    }
    else {
        cerr << "Файл '" << filename << "' не существует или не удалось открыть.\n";
        return;
    }
}