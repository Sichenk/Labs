#include "search_in_file.h"
#include "game.h"
#include <fstream>
#include <iostream>

using namespace std;

void searchInFile(string& filename) {
    string fullPath = "C:\\" + filename;
    ifstream inFile(fullPath);

    if (!inFile.is_open()) {
        cerr << "�� ������� ������� ���� ��� ������ ������.\n";
        return;
    }

    // ���������� ������������ ������
    string header;
    getline(inFile, header);

    string fieldToSearch;
    string searchKey;

    cout << "������� ���� ��� ������ (��������/������/�������): ";
    cin.ignore();
    getline(cin, fieldToSearch);

    Game game;
    bool found = false;

    if (fieldToSearch == "��������") {
        cout << "������� �������� ���� ��� ������: ";
        getline(cin, searchKey);

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
                cout << "�������� ����: " << game.title << ", �������� ������������: " << game.diskSpaceMB
                    << " ��, �������� �������: " << game.graphicsQuality << "\n";
            }
        }
    }
    else if (fieldToSearch == "������") {
        cout << "������� �������� ������������ ���� ��� ������: ";
        getline(cin, searchKey);

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
                cout << "�������� ����: " << game.title << ", �������� ������������: " << game.diskSpaceMB
                    << " ��, �������� �������: " << game.graphicsQuality << "\n";
            }
        }
    }
    else if (fieldToSearch == "�������") {
        cout << "������� �������� ������� ���� ��� ������: ";
        getline(cin, searchKey);

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
                cout << "�������� ����: " << game.title << ", �������� ������������: " << game.diskSpaceMB
                    << " ��, �������� �������: " << game.graphicsQuality << "\n";
            }
        }
    }
    else {
        cerr << "������������ ���� ��� ������.\n";
        return;
    }

    if (!found) {
        cout << "������ �� �������.\n";
    }

    inFile.close();
}