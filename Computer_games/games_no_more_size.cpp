#include <iostream>
#include <fstream>
#include <iomanip>
#include "games_no_more_size.h"

using namespace std;

void gamesNoMoreCertainSize(string& filename, vector<Game>& games) {
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

    int maxSizeMB;
    cout << "Введите объем на диске для вывода всех записей с объемом не более данного: ";
    while (true) {
        try {
            cin >> maxSizeMB;
            if (cin.fail()) {
                throw invalid_argument("Ошибка: введено не число.\n");
            }
            if (maxSizeMB <= 0) {
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

    string secondFileName;
    cout << "Введите имя файла для записи всех игр с объемом не более данного: ";
    cin.ignore();
    getline(cin, secondFileName);

    while (secondFileName == "temp.txt") {
        cerr << "Нельзя использовать данное имя для создания файла.\n";
        cerr << "Пожалуйста введите корректное имя файла: ";
        secondFileName.clear();
        getline(cin, secondFileName);
    }

    ofstream outFile("C:\\" + secondFileName);
    cout << setw(50) << left << "Название игры" << "|"
        << setw(50) << left << "Графика игры" << endl;
    outFile << setw(50) << left << "Название игры" << "|"
        << setw(50) << left << "Графика игры" << endl;
    for (const auto& game : games) {
        if (game.diskSpaceMB <= maxSizeMB) {
            cout << setw(50) << left << game.title << "|"
                << setw(50) << left << game.graphicsQuality << "\n";
            outFile << setw(50) << left << game.title << "|"
                << setw(50) << left << game.graphicsQuality << "\n";
        }
    }

    inFile.close();
    outFile.close();
}