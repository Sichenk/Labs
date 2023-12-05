#include "create_first_file.h"
#include "open_file.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void createFirstFile(string& filename) {
    cout << "Введите имя файла: ";
    cin.ignore();
    getline(cin, filename);

    while (filename == "temp.txt") {
        cerr << "Нельзя использовать данное название для создания файла.\n";
        cerr << "Пожалуйста введите корректное название файла: ";
        filename.clear();
        getline(cin, filename);
    }

    string fullPath = "C:\\" + filename;

    ifstream fileExists(fullPath.c_str());
    if (fileExists) {
        cerr << "Файл с именем '" << filename << "' уже существует." << endl;
        return;
    }

    ofstream outFile(fullPath, ios::binary);

    if (outFile.is_open()) {
        cout << "Файл '" << filename << "' успешно создан в C:\\" << endl;
        outFile << setw(50) << left << "Название игры" << "|"
            << setw(50) << left << "Сколько места игра занимает на диске" << "|"
            << setw(50) << left << "Графика игры" << "\n";
        outFile.close();
    }
    else {
        cerr << "Не удалось создать файл." << endl;
        return;
    }
}