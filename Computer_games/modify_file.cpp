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
        cerr << "Не удалось открыть файл для редактирования записей.\n";
        return;
    }

    // Пропустить заголовочную строку
    string header;
    getline(inFile, header);

    string fieldToEdit;
    string searchKey;
    string newValue;
    bool found = false;

    cout << "Введите поле для редактирования (название/память/графика): ";
    cin.ignore();
    getline(cin, fieldToEdit);

    Game game;
    outFile << setw(50) << left << "Название игры" << "|"
        << setw(50) << left << "Сколько места игра занимает на диске" << "|"
        << setw(50) << left << "Графика игры" << "\n";
    if (fieldToEdit == "название") {
        cout << "Введите название игры для редактирования: ";
        getline(cin, searchKey);

        cout << "Введите новое значение: ";
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
    else if (fieldToEdit == "память") {
        cout << "Введите дисковое пространство игры для редактирования: ";
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

        cout << "Введите новое значение: ";
        int newValue;
        while (true) {
            try {
                cin >> newValue;
                if (cin.fail()) {
                    throw invalid_argument("Ошибка: введено не число.\n");
                }
                if (newValue <= 0) {
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
    else if (fieldToEdit == "графика") {
        cout << "Введите качество графики игры для редактирования: ";
        getline(cin, searchKey);

        while (searchKey != "плохая" && searchKey != "хорошая") {
            cout << "Ошибка: качество графики должно быть в формате плохая/хорошая." << endl;
            cout << "Пожалуйста, введите корректное значение: ";
            searchKey.clear();
            getline(cin, searchKey);
        }

        cout << "Введите новое значение: ";
        getline(cin, newValue);

        while (newValue != "плохая" && newValue != "хорошая") {
            cout << "Ошибка: качество графики должно быть в формате плохая/хорошая." << endl;
            cout << "Пожалуйста, введите корректное значение: ";
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
        cerr << "Некорректное поле для поиска.\n";
        return;
    }
    searchKey.clear();
    newValue.clear();

    inFile.close();
    outFile.close();

    if (found) {
        if (remove(fullPath.c_str()) != 0 || rename("C:\\temp.txt", fullPath.c_str()) != 0) {
            cerr << "Ошибка при замене файла.\n";
            return;
        }
        cout << "Запись успешно отредактирована.\n";
    }
    else {
        remove("C:\\temp.txt");
        cout << "Запись не найдена.\n";
    }

    return;
}