#include "add_to_file.h"
#include "game.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void addToFile(string& filename) {
    string fullPath = "C:\\" + filename;

    ofstream outFile(fullPath, ios::app | ios::binary);  // ��������� ���� ��� ���������� ������� � �����

    if (!outFile.is_open()) {
        cerr << "�� ������� ������� ���� ��� ���������� �������.\n";
        return;
    }

    Game newGame;

    cout << "������� ������ �� ����:\n";

    cout << "�������� ����: ";
    cin.ignore();
    getline(cin, newGame.title);

    cout << "������� ����� ���� �������� �� ����� (� ����������): ";
    while (true) {
        try {
            cin >> newGame.diskSpaceMB;
            if (cin.fail()) {
                throw invalid_argument("������: ������� �� �����.\n");
            }
            if (newGame.diskSpaceMB <= 0) {
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

    cout << "������� ����: ";
    cin.ignore();
    getline(cin, newGame.graphicsQuality);
    while (newGame.graphicsQuality != "�������" && newGame.graphicsQuality != "������") {
        cout << "���������� ������� ������ � ������� � �������: �������/������" << endl;
        cout << "������� ����: ";
        cin.ignore();
        getline(cin, newGame.graphicsQuality);
    }

    outFile << setw(50) << left << newGame.title << "|"
        << setw(50) << left << newGame.diskSpaceMB << "|"
        << setw(50) << left << newGame.graphicsQuality << "\n";

    outFile.close();
    cout << "������ ������� ��������� � ����.\n";
    return;
}