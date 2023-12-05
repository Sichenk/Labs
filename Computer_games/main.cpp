#include <iostream>
#include <fstream>
#include "create_first_file.h"
#include "add_to_file.h"
#include "open_file.h"
#include "read_from_file.h"
#include "delete_from_file.h"
#include "modify_file.h"
#include "search_in_file.h"
#include "create_second_file.h"
#include "sort_file.h"
#include "games_no_more_size.h"
#include <windows.h>

using namespace std;

#define SIZE 901

void theMenu() {
    cout << "����:" << endl;
    cout << "1. ������� ���� �� �����." << endl;
    cout << "2. ������� ��� ������������ ����." << endl;
    cout << "3. ���������� ������ � ����." << endl;
    cout << "4. ��������� � ������� ���������� ����� �� �����." << endl;
    cout << "5. �������� ������ �� �����." << endl;
    cout << "6. �������� ��������� ���� �����." << endl;
    cout << "7. ����� ������ � ����� �� �����." << endl;
    cout << "8. �������� ������� ����� �� ������ ���������." << endl;
    cout << "9. ����������� � ����������� ������ �� ����������." << endl;
    cout << "10. ����� ���� ���, ����� ������� �� ����� ���������." << endl;
    cout << "0. �����" << endl;
}

int hashFunction(const string& str) {
    int hash = 0;
    for (int i = 0; i < str.length(); ++i) {
        hash += (i + 1) * static_cast<size_t>(str[i]);
    }
    return hash % SIZE;
}

bool checkUser(int userHash, int passwordHash) {
    return (userHash == hashFunction("������������") &&
        passwordHash == hashFunction("������"));
}

int main() {
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string username, password;
    cout << "������� ��� ������������: ";
    cin >> username;
    cout << "������� ������: ";
    cin >> password;

    int userHash = hashFunction(username);
    int passwordHash = hashFunction(password);

    while (!checkUser(userHash, passwordHash)) {
        cout << "������ ������������� ������������. ��������� �������." << endl;
        cout << "������� ��� ������������: ";
        cin >> username;
        cout << "������� ������: ";
        cin >> password;

        userHash = hashFunction(username);
        passwordHash = hashFunction(password);
    }
    cout << "������������ ������� ���������������." << endl;

    string filename;

    int choice;
    theMenu();
    do {
        cout << endl << "������� ��� �����: ";
        choice = 0;

        try {
            cin.clear();
            cin >> choice;
            if (cin.fail()) {
                throw runtime_error("������: ������� �� �����.");
            }
        }
        catch (const exception& e) {
            cin.clear();
            cin.ignore(9999, '\n');
            cerr << e.what() << endl;
            choice = -1;
        }

        switch (choice) {
        case 1: {
            createFirstFile(filename);
            break;
        }
        case 2: {
            openFile(filename);
            break;
        }
        case 3: {
            addToFile(filename);
            break;
        }
        case 4: {
            readFromFile(filename);
            break;
        }
        case 5: {
            deleteFromFile(filename);
            break;
        }
        case 6: {
            modifyFile(filename);
            break;
        }
        case 7: {
            searchInFile(filename);
            break;
        }
        case 8: {
            createSecondFile(filename);
            break;
        }
        case 9: {
            vector<Game> games;
            sortFile(filename, games);
            break;
        }
        case 10: {
            vector<Game> games;
            gamesNoMoreCertainSize(filename, games);
            break;
        }
        case 0: {
            cout << "����� �� ���������.\n";
            break;
        }
        default: {
            cout << "�������� �����. ������� �������������� �������.\n";
            break;
        }
        }

    } while (choice != 0);

    return 0;
}