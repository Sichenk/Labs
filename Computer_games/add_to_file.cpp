#include "add_to_file.h"
#include "game.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void addToFile(string& filename) {
    string fullPath = "C:\\" + filename;

    ofstream outFile(fullPath, ios::app | ios::binary);  // Открываем файл для добавления записей в конец

    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для добавления записей.\n";
        return;
    }

    Game newGame;

    cout << "Введите данные об игре:\n";

    cout << "Название игры: ";
    cin.ignore();
    getline(cin, newGame.title);

    cout << "Сколько места игра занимает на диске (в мегабайтах): ";
    while (true) {
        try {
            cin >> newGame.diskSpaceMB;
            if (cin.fail()) {
                throw invalid_argument("Ошибка: введено не число.\n");
            }
            if (newGame.diskSpaceMB <= 0) {
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

    cout << "Графика игры: ";
    cin.ignore();
    getline(cin, newGame.graphicsQuality);
    while (newGame.graphicsQuality != "хорошая" && newGame.graphicsQuality != "плохая") {
        cout << "Пожалуйста введите данные о графике в формате: хорошая/плохая" << endl;
        cout << "Графика игры: ";
        cin.ignore();
        getline(cin, newGame.graphicsQuality);
    }

    outFile << setw(50) << left << newGame.title << "|"
        << setw(50) << left << newGame.diskSpaceMB << "|"
        << setw(50) << left << newGame.graphicsQuality << "\n";

    outFile.close();
    cout << "Запись успешно добавлена в файл.\n";
    return;
}