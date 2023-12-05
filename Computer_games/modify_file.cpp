#include "modify_file.h"
#include "game.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

void modifyFile(string& filename) {
    string fullPath = "C:\\" + filename;
    ifstream inFile(fullPath);
    ofstream outFile("C:\\temp.txt", ios::app | ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "�� ������� ������� ���� ��� �������������� �������.\n";
        return;
    }

    // ���������� ������������ ������
    string header;
    getline(inFile, header);

    string fieldToEdit;
    string searchKey;
    string newValue;
    bool found = false;

    cout << "������� ���� ��� �������������� (��������/������/�������): ";
    cin.ignore();
    getline(cin, fieldToEdit);

    Game game;
    outFile << setw(50) << left << "�������� ����" << "|"
        << setw(50) << left << "������� ����� ���� �������� �� �����" << "|"
        << setw(50) << left << "������� ����" << "\n";
    if (fieldToEdit == "��������") {
        cout << "������� �������� ���� ��� ��������������: ";
        getline(cin, searchKey);

        cout << "������� ����� ��������: ";
        getline(cin, newValue);

        while (getline(inFile >> ws, game.title, '|')) {
            inFile >> game.diskSpaceMB;
            inFile.ignore(100, '|');
            getline(inFile >> ws, game.graphicsQuality, ' ');

            size_t endpos = game.title.find_last_not_of(" \t");
            if (string::npos != endpos) {
                game.title = game.title.substr(0, endpos + 1);
            }

            if (game.title == searchKey) {
                found = true;
                game.title = newValue;

                outFile << setw(50) << left << game.title << "|"
                    << setw(50) << left << game.diskSpaceMB << "|"
                    << setw(50) << left << game.graphicsQuality << "\n";
            }
            else {
                outFile << setw(50) << left << game.title << "|"
                    << setw(50) << left << game.diskSpaceMB << "|"
                    << setw(50) << left << game.graphicsQuality << "\n";
            }
        }
    }
    else if (fieldToEdit == "������") {
        cout << "������� �������� ������������ ���� ��� ��������������: ";
        int searchValue;
        while (true) {
            try {
                cin >> searchValue;
                if (cin.fail()) {
                    throw invalid_argument("������: ������� �� �����.\n");
                }
                if (searchValue <= 0) {
                    throw out_of_range("������: ������� ������������� �����.\n");
                }
                break;
            }
            catch (const exception& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << e.what() << "����������, ������� ���������� ��������: ";
            }
        }

        cout << "������� ����� ��������: ";
        int newValue;
        while (true) {
            try {
                cin >> newValue;
                if (cin.fail()) {
                    throw invalid_argument("������: ������� �� �����.\n");
                }
                if (newValue <= 0) {
                    throw out_of_range("������: ������� ������������� �����.\n");
                }
                break;
            }
            catch (const exception& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << e.what() << "����������, ������� ���������� ��������: ";
            }
        }

        while (getline(inFile >> ws, game.title, '|')) {
            inFile >> game.diskSpaceMB;
            inFile.ignore(100, '|');
            getline(inFile >> ws, game.graphicsQuality, ' ');

            size_t endpos = game.title.find_last_not_of(" \t");
            if (string::npos != endpos) {
                game.title = game.title.substr(0, endpos + 1);
            }

            if (game.diskSpaceMB == searchValue) {
                found = true;
                game.diskSpaceMB = newValue;

                outFile << setw(50) << left << game.title << "|"
                    << setw(50) << left << game.diskSpaceMB << "|"
                    << setw(50) << left << game.graphicsQuality << "\n";
            }
            else {
                outFile << setw(50) << left << game.title << "|"
                    << setw(50) << left << game.diskSpaceMB << "|"
                    << setw(50) << left << game.graphicsQuality << "\n";
            }
        }
    }
    else if (fieldToEdit == "�������") {
        cout << "������� �������� ������� ���� ��� ��������������: ";
        getline(cin, searchKey);

        while (searchKey != "������" && searchKey != "�������") {
            cout << "������: �������� ������� ������ ���� � ������� ������/�������." << endl;
            cout << "����������, ������� ���������� ��������: ";
            searchKey.clear();
            getline(cin, searchKey);
        }

        cout << "������� ����� ��������: ";
        getline(cin, newValue);

        while (newValue != "������" && newValue != "�������") {
            cout << "������: �������� ������� ������ ���� � ������� ������/�������." << endl;
            cout << "����������, ������� ���������� ��������: ";
            newValue.clear();
            getline(cin, newValue);
        }

        while (getline(inFile >> ws, game.title, '|')) {
            inFile >> game.diskSpaceMB;
            inFile.ignore(100, '|');
            getline(inFile >> ws, game.graphicsQuality, ' ');

            size_t endpos = game.title.find_last_not_of(" \t");
            if (string::npos != endpos) {
                game.title = game.title.substr(0, endpos + 1);
            }

            if (game.graphicsQuality == searchKey) {
                found = true;
                game.graphicsQuality = newValue;

                outFile << setw(50) << left << game.title << "|"
                    << setw(50) << left << game.diskSpaceMB << "|"
                    << setw(50) << left << game.graphicsQuality << "\n";
            }
            else {
                outFile << setw(50) << left << game.title << "|"
                    << setw(50) << left << game.diskSpaceMB << "|"
                    << setw(50) << left << game.graphicsQuality << "\n";
            }
        }
    }
    else {
        cerr << "������������ ���� ��� ������.\n";
        return;
    }
    searchKey.clear();
    newValue.clear();

    inFile.close();
    outFile.close();

    if (found) {
        if (remove(fullPath.c_str()) != 0 || rename("C:\\temp.txt", fullPath.c_str()) != 0) {
            cerr << "������ ��� ������ �����.\n";
            return;
        }
        cout << "������ ������� ���������������.\n";
    }
    else {
        remove("C:\\temp.txt");
        cout << "������ �� �������.\n";
    }

    return;
}