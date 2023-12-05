#include "search_in_file.h"
#include "game.h"
#include <fstream>
#include <iostream>

using namespace std;

void searchInFile(string& filename) {
    string fullPath = "C:\\" + filename;
    ifstream inFile(fullPath);

    if (!inFile.is_open()) {
        cerr << "Не удается открыть файл для поиска данных.\n";
        return;
    }

    // Пропустить заголовочную строку
    string header;
    getline(inFile, header);

    string fieldToSearch;
    string searchKey;

    cout << "Введите поле для поиска (название/память/графика): ";
    cin.ignore();
    getline(cin, fieldToSearch);

    Game game;
    bool found = false;

    if (fieldToSearch == "название") {
        cout << "Введите название игры для поиска: ";
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
                cout << "Название игры: " << game.title << ", Дисковое пространство: " << game.diskSpaceMB
                    << " МБ, Качество графики: " << game.graphicsQuality << "\n";
            }
        }
    }
    else if (fieldToSearch == "память") {
        cout << "Введите дисковое пространство игры для поиска: ";
        getline(cin, searchKey);

        int searchValue;
        while (true) {
            try {
                cin >> searchValue;
                if (cin.fail()) {
                    throw invalid_argument("Ошибка: введено не число.\n");
                }
                if (searchValue <= 0) {
                    throw out_of_range("Ошибка: введите положительное число.\n");
                }
                break;
            }
            catch (const exception& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << e.what() << "Пожалуйста, введите корректное значение: ";
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
                cout << "Название игры: " << game.title << ", Дисковое пространство: " << game.diskSpaceMB
                    << " МБ, Качество графики: " << game.graphicsQuality << "\n";
            }
        }
    }
    else if (fieldToSearch == "графика") {
        cout << "Введите качество графики игры для поиска: ";
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
                cout << "Название игры: " << game.title << ", Дисковое пространство: " << game.diskSpaceMB
                    << " МБ, Качество графики: " << game.graphicsQuality << "\n";
            }
        }
    }
    else {
        cerr << "Некорректное поле для поиска.\n";
        return;
    }

    if (!found) {
        cout << "Запись не найдена.\n";
    }

    inFile.close();
}