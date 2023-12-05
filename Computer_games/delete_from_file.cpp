#include "delete_from_file.h"
#include "game.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void deleteFromFile(string& filename) {
    string fullPath = "C:\\" + filename;
    ifstream inFile(fullPath);
    ofstream outFile("C:\\temp.txt", ios::app | ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Не удалось открыть файл для удаления записи.\n";
        return;
    }

    // Пропустить заголовочную строку
    string header;
    getline(inFile, header);

    string titleToDelete;
    bool found = false;

    cout << "Введите название игры, которую вы хотите удалить: ";
    cin.ignore();
    getline(cin, titleToDelete);

    Game game;
    outFile << setw(50) << left << "Название игры" << "|"
        << setw(50) << left << "Сколько места игра занимает на диске" << "|"
        << setw(50) << left << "Графика игры" << "\n";

    while (getline(inFile >> ws, game.title, '|')) {
        inFile >> game.diskSpaceMB;
        inFile.ignore(100, '|');
        getline(inFile >> ws, game.graphicsQuality, ' ');

        size_t endpos = game.title.find_last_not_of(" \t");
        if (string::npos != endpos) {
            game.title = game.title.substr(0, endpos + 1);
        }


        if (game.title == titleToDelete) {
            found = true;
            cout << "Запись с названием '" << titleToDelete << "' удалена успешно.\n";
        }
        else {
            outFile << setw(50) << left << game.title << "|"
                << setw(50) << left << game.diskSpaceMB << "|"
                << setw(50) << left << game.graphicsQuality << "\n";
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        if (remove(fullPath.c_str()) != 0 || rename("C:\\temp.txt", fullPath.c_str()) != 0) {
            cerr << "Ошибка при замене файла.\n";
            return;
        }
    }
    else {
        remove("C:\\temp.txt");
        cout << "Запись не найдена.\n";
    }

    return;
}