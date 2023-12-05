#include "create_first_file.h"
#include "open_file.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void createFirstFile(string& filename) {
    cout << "������� ��� �����: ";
    cin.ignore();
    getline(cin, filename);

    while (filename == "temp.txt") {
        cerr << "������ ������������ ������ �������� ��� �������� �����.\n";
        cerr << "���������� ������� ���������� �������� �����: ";
        filename.clear();
        getline(cin, filename);
    }

    string fullPath = "C:\\" + filename;

    ifstream fileExists(fullPath.c_str());
    if (fileExists) {
        cerr << "���� � ������ '" << filename << "' ��� ����������." << endl;
        return;
    }

    ofstream outFile(fullPath, ios::binary);

    if (outFile.is_open()) {
        cout << "���� '" << filename << "' ������� ������ � C:\\" << endl;
        outFile << setw(50) << left << "�������� ����" << "|"
            << setw(50) << left << "������� ����� ���� �������� �� �����" << "|"
            << setw(50) << left << "������� ����" << "\n";
        outFile.close();
    }
    else {
        cerr << "�� ������� ������� ����." << endl;
        return;
    }
}