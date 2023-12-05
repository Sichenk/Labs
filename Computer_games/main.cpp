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
    cout << "Меню:" << endl;
    cout << "1. Создать файл на диске." << endl;
    cout << "2. Открыть уже существующий файл." << endl;
    cout << "3. Добавление записи в файл." << endl;
    cout << "4. Прочитать и вывести содержимое файла на экран." << endl;
    cout << "5. Удаление записи из файла." << endl;
    cout << "6. Изменить отдельное поле файла." << endl;
    cout << "7. Поиск данных в файле по ключу." << endl;
    cout << "8. Создание второго файла на основе исходного." << endl;
    cout << "9. Сортировать и фильтровать данные по параметрам." << endl;
    cout << "10. Вывод всех игр, объем которых не более заданного." << endl;
    cout << "0. Выход" << endl;
}

int hashFunction(const string& str) {
    int hash = 0;
    for (int i = 0; i < str.length(); ++i) {
        hash += (i + 1) * static_cast<size_t>(str[i]);
    }
    return hash % SIZE;
}

bool checkUser(int userHash, int passwordHash) {
    return (userHash == hashFunction("пользователь") &&
        passwordHash == hashFunction("пароль"));
}

int main() {
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string username, password;
    cout << "Введите имя пользователя: ";
    cin >> username;
    cout << "Введите пароль: ";
    cin >> password;

    int userHash = hashFunction(username);
    int passwordHash = hashFunction(password);

    while (!checkUser(userHash, passwordHash)) {
        cout << "Ошибка идентификации пользователя. Повторите попытку." << endl;
        cout << "Введите имя пользователя: ";
        cin >> username;
        cout << "Введите пароль: ";
        cin >> password;

        userHash = hashFunction(username);
        passwordHash = hashFunction(password);
    }
    cout << "Пользователь успешно идентифицирован." << endl;

    string filename;

    int choice;
    theMenu();
    do {
        cout << endl << "Введите ваш выбор: ";
        choice = 0;

        try {
            cin.clear();
            cin >> choice;
            if (cin.fail()) {
                throw runtime_error("Ошибка: введено не число.");
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
            cout << "Выход из программы.\n";
            break;
        }
        default: {
            cout << "Неверный выбор. Введите действительный вариант.\n";
            break;
        }
        }

    } while (choice != 0);

    return 0;
}