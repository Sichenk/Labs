#include "create_first_file.h"
#include <iostream>
#include <fstream>

using namespace std;

void createSecondFile(string& filename) {
    string fullPath = "C:\\" + filename;
    ifstream inFile(fullPath);

    if (!inFile.is_open()) {
        cerr << "Не удалось открыть исходный файл.\n";
        return;
    }

    // Запрос у пользователя названия второго файла
    string secondFileName;
    cout << "Введите имя второго файла: ";
    cin.ignore();
    getline(cin, secondFileName);

    while (secondFileName == "temp.txt") {
        cerr << "Нельзя использовать данное имя для создания файла.\n";
        cerr << "Пожалуйста введите корректное имя файла: ";
        secondFileName.clear();
        getline(cin, secondFileName);
    }

    // Открываем второй файл для записи
    ofstream outFile("C:\\" + secondFileName);

    if (!outFile.is_open()) {
        cerr << "Не удалось открыть второй файл для записи.\n";
        inFile.close();
        return;
    }

    // Читаем данные из исходного файла и записываем во второй файл
    string line;

    while (getline(inFile, line)) {
        outFile << line << "\n";
    }

    // Закрываем файлы
    inFile.close();
    outFile.close();

    cout << "Второй файл успешно создан на основе исходного.\n";

    return;
}