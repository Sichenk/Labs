#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "sort_file.h"

using namespace std;

bool compareByField(Game& a, Game& b, const string& field) {
    if (field == "название") {
        return a.title < b.title;
    }
    else if (field == "память") {
        return a.diskSpaceMB < b.diskSpaceMB;
    }
    else if (field == "графика") {
        return a.graphicsQuality < b.graphicsQuality;
    }
    return false;
}

void sortFile(string& filename, vector<Game>& games) {
    string fullPath = "C:\\" + filename;
    ifstream inFile(fullPath);
    if (!inFile.is_open()) {
        cerr << "Не удалось открыть файл для чтения.\n";
        return;
    }
    string header;
    getline(inFile, header);

    Game game;
    while (getline(inFile >> ws, game.title, '|')) {
        inFile >> game.diskSpaceMB;
        inFile.ignore(100, '|');
        getline(inFile >> ws, game.graphicsQuality, ' ');

        size_t endpos = game.title.find_last_not_of(" \t");
        if (string::npos != endpos) {
            game.title = game.title.substr(0, endpos + 1);
        }
        games.push_back(game);
    }

    inFile.close();

    string fieldToSort;
    cout << "Введите поле, по которому нужно отсортировать (название/память/графика): ";
    cin.ignore();
    getline(cin, fieldToSort);

    while (fieldToSort != "название" && fieldToSort != "память" && fieldToSort != "графика") {
        cerr << "Некорректное название поля.\n";
        cerr << "Повторите попытку ввода: ";
        fieldToSort.clear();
        cin >> fieldToSort;
    }

    // Запрос у пользователя тип сортировки (по возрастанию или убыванию)
    string sortOrder;
    cout << "Введите порядок сортировки (asc/desc): ";
    cin >> sortOrder;

    while (sortOrder != "asc" && sortOrder != "desc") {
        cerr << "Некорректный порядок сортировки.\n";
        cerr << "Повторите попытку ввода: ";
        sortOrder.clear();
        cin >> sortOrder;
    }

    // Сортировка в зависимости от порядка
    if (sortOrder == "asc") {
        sort(games.begin(), games.end(), [fieldToSort](Game& a, Game& b) {
            return compareByField(a, b, fieldToSort);
        });
    }
    else if (sortOrder == "desc") {
        sort(games.rbegin(), games.rend(), [fieldToSort](Game& a, Game& b) {
            return compareByField(a, b, fieldToSort);
        });
    }

    ofstream outFile(fullPath);
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для записи.\n";
        return;
    }

    outFile << setw(50) << left << "Название игры" << "|"
        << setw(50) << left << "Сколько места игра занимает на диске" << "|"
        << setw(50) << left << "Графика игры" << "\n";

    for (const auto& game : games) {
        outFile << setw(50) << left << game.title << "|"
            << setw(50) << left << game.diskSpaceMB << "|"
            << setw(50) << left << game.graphicsQuality << "\n";
    }

    outFile.close();
    cout << "Записи успешно отсортированы." << endl;
}