#include "create_first_file.h"
#include <iostream>
#include <fstream>

using namespace std;

void createSecondFile(string& filename) {
    string fullPath = "C:\\" + filename;
    ifstream inFile(fullPath);

    if (!inFile.is_open()) {
        cerr << "�� ������� ������� �������� ����.\n";
        return;
    }

    // ������ � ������������ �������� ������� �����
    string secondFileName;
    cout << "������� ��� ������� �����: ";
    cin.ignore();
    getline(cin, secondFileName);

    while (secondFileName == "temp.txt") {
        cerr << "������ ������������ ������ ��� ��� �������� �����.\n";
        cerr << "���������� ������� ���������� ��� �����: ";
        secondFileName.clear();
        getline(cin, secondFileName);
    }

    // ��������� ������ ���� ��� ������
    ofstream outFile("C:\\" + secondFileName);

    if (!outFile.is_open()) {
        cerr << "�� ������� ������� ������ ���� ��� ������.\n";
        inFile.close();
        return;
    }

    // ������ ������ �� ��������� ����� � ���������� �� ������ ����
    string line;

    while (getline(inFile, line)) {
        outFile << line << "\n";
    }

    // ��������� �����
    inFile.close();
    outFile.close();

    cout << "������ ���� ������� ������ �� ������ ���������.\n";

    return;
}