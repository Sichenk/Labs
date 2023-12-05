#include "open_file.h"
#include <iostream>
#include <fstream>

using namespace std;

void openFile(string& filename) {
    cout << "������� ��� �����: ";
    cin.ignore();
    getline(cin, filename);
    string fullPath = "C:\\" + filename;

    ifstream outFile(fullPath, ios::binary);
    if (outFile.is_open()) {
        cout << "���� '" << filename << "' ������� ������.\n";
        outFile.close();

    }
    else {
        cerr << "���� '" << filename << "' �� ���������� ��� �� ������� �������.\n";
        return;
    }
}