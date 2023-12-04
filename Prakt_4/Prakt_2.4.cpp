#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>
#include <string>
#include <winsock2.h>
#include <sstream>
#include <windows.h>
#include <chrono>
#include <iomanip>
#include <nlohmann/json.hpp>

#pragma comment(lib, "ws2_32.lib")

#define SIZE 1901

std::mutex dbMutex;
std::mutex jsonMutex;

struct HashTable {
    std::string keys[SIZE];
    std::string values[SIZE];
    int count;
};

unsigned int firstHash(const std::string& key) {
    unsigned int hash = 0;
    for (char ch : key) {
        hash = hash * 31 + ch;
    }
    return hash % SIZE;
}

unsigned int secondHash(const std::string& str) {
    return 7 - (firstHash(str) % 7);
}

void HSET(HashTable& hashtable, std::string& key, std::string& value);

void fileUpdate(const std::string& filename, HashTable& hashTable) {
    std::ofstream file(filename);
    file << "HASHTABLE:\n";
    for (int i = 0; i < SIZE; i++) {
        if (!hashTable.values[i].empty() && !hashTable.keys[i].empty()) {
            file << hashTable.keys[i] << "\n" << hashTable.values[i] << "\n";
        }
    }
    file.close();
}

void copyingValuesFromFile(std::ifstream& file, HashTable& hashTable) {
    std::string line;

    std::string header;
    getline(file, header);

    std::string key;
    while (getline(file, line)) {
        if (key.empty()) {
            key = line;
        }
        else {
            std::string value = line;
            HSET(hashTable, key, value);
            key.clear();
        }
    }
    file.close();
}

class Server {
public:
    Server(SOCKET client_socket) : client_socket(client_socket) {
        queryProcessing(client_socket);
    }
private:
    SOCKET client_socket;
    
    void generateHierarchy(const nlohmann::json& visits, nlohmann::json& hierarchy, std::string& firstDimension, std::string& secondDimension, std::string& thirdDimension) {
        int id = 1;
        int parent_id = NULL;
        int count = 1;
        if (firstDimension == "URL") {
            if (secondDimension == "SourceIP") {
                if (thirdDimension == "TimeInterval") {
                    for (const auto& visit : visits) {
                        // Проверка наличия поля "URL" в текущем узле
                        if (visit.find("URL") != visit.end()) {
                            // Извлечение значения поля "URL"
                            std::string url = visit["URL"].get<std::string>();

                            std::string sourceIP = visit.at("SourceIP").get<std::string>();
                            std::string timeValue = visit.at("Time").get<std::string>();

                            std::istringstream timeStream(timeValue);
                            std::tm tm = {};
                            std::istringstream ss(timeValue);
                            ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

                            // Выдергиваем часы и минуты
                            int hours = tm.tm_hour;
                            int minutes = tm.tm_min;

                            // Добавляем одну минуту
                            auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                            auto timePointPlusOneMinute = timePoint + std::chrono::minutes(1);

                            // Преобразование обратно в std::tm
                            std::time_t timeT = std::chrono::system_clock::to_time_t(timePointPlusOneMinute);
                            std::tm tmPlusOneMinute = *std::localtime(&timeT);

                            // Выдергиваем обновленные часы и минуты
                            int hoursPlusOneMinute = tmPlusOneMinute.tm_hour;
                            int minutesPlusOneMinute = tmPlusOneMinute.tm_min;

                            // Запись интервала
                            std::ostringstream resultStringStream;
                            resultStringStream << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes
                                << "-" << std::setfill('0') << std::setw(2) << hoursPlusOneMinute << ":" << std::setw(2) << minutesPlusOneMinute;

                            // Проходим по всему массиву hierarchy
                            bool found = false;
                            for (auto& node : hierarchy) {
                                // Проверяем, имеет ли у текущей записи поля "URL", "TimeInterval"
                                if (node.find("URL") != node.end() && !node["URL"].is_null() &&
                                    node.find("SourceIP") != node.end() && !node["SourceIP"].is_null() &&
                                    node.find("TimeInterval") != node.end() && !node["TimeInterval"].is_null()) {

                                    std::string timeInterval = node.at("TimeInterval").get<std::string>();

                                    // Находим позицию тире ("-") в строке
                                    size_t dashPosition = timeInterval.find('-');
                                    int startHours = 0, startMinutes = 0, endHours = 0, endMinutes = 0;

                                    if (dashPosition != std::string::npos) {
                                        // Получаем начальное и конечное время
                                        std::string startTime = timeInterval.substr(0, dashPosition);
                                        std::string endTime = timeInterval.substr(dashPosition + 1);

                                        // Находим позицию двоеточия (":") в начальном времени
                                        size_t colonPositionStart = startTime.find(':');

                                        if (colonPositionStart != std::string::npos) {
                                            // Выделяем часы и минуты из начального времени
                                            std::string startHoursStr = startTime.substr(0, colonPositionStart);
                                            std::string startMinutesStr = startTime.substr(colonPositionStart + 1);

                                            // Преобразуем строки в числа
                                            startHours = std::stoi(startHoursStr);
                                            startMinutes = std::stoi(startMinutesStr);
                                        }

                                        // Находим позицию двоеточия (":") в конечном времени
                                        size_t colonPositionEnd = endTime.find(':');

                                        if (colonPositionEnd != std::string::npos) {
                                            // Выделяем часы и минуты из конечного времени
                                            std::string endHoursStr = endTime.substr(0, colonPositionEnd);
                                            std::string endMinutesStr = endTime.substr(colonPositionEnd + 1);

                                            // Преобразуем строки в числа
                                            endHours = std::stoi(endHoursStr);
                                            endMinutes = std::stoi(endMinutesStr);
                                        }
                                    }
                                    // Проверяем, совпадает ли URL, IP и диапазон времени
                                    if (node["URL"] == url && node["SourceIP"].get<std::string>() == sourceIP && minutes >= startMinutes && minutes < endMinutes && hours >= startHours && hours <= endHours) {
                                        // Увеличиваем count на 1
                                        node["Count"] = node["Count"].get<int>() + 1;
                                        found = true;
                                        break;
                                    }
                                }
                            }
                            if (found == false) {
                                // Если URL не был найден в существующих записях, добавляем новую запись
                                nlohmann::json newNode = {
                                    {"Id", id},
                                    {"Pid", parent_id},
                                    {"URL", url},
                                    {"SourceIP", sourceIP},
                                    {"TimeInterval", resultStringStream.str()},
                                    {"Count", count}
                                };
                                hierarchy.push_back(newNode);
                                parent_id = id;
                                id++;
                            }
                        }
                    }
                }
                else {
                    for (const auto& visit : visits) {
                        // Проверка наличия поля "URL" в текущем узле
                        if (visit.find("URL") != visit.end()) {
                            // Извлечение значения поля "URL"
                            std::string url = visit["URL"].get<std::string>();

                            std::string sourceIP = visit.at("SourceIP").get<std::string>();

                            // Проходим по всему массиву hierarchy
                            bool found = false;
                            for (auto& node : hierarchy) {
                                // Проверяем, имеет ли у текущей записи поля "URL", "TimeInterval"
                                if (node.find("URL") != node.end() && !node["URL"].is_null() &&
                                    node.find("SourceIP") != node.end() && !node["SourceIP"].is_null()) {

                                    // Проверяем, совпадает ли URL, IP и диапазон времени
                                    if (node["URL"] == url && node["SourceIP"].get<std::string>() == sourceIP) {
                                        // Увеличиваем count на 1
                                        node["Count"] = node["Count"].get<int>() + 1;
                                        found = true;
                                        break;
                                    }
                                }
                            }
                            if (found == false) {
                                // Если URL не был найден в существующих записях, добавляем новую запись
                                nlohmann::json newNode = {
                                    {"Id", id},
                                    {"Pid", parent_id},
                                    {"URL", url},
                                    {"SourceIP", sourceIP},
                                    {"Count", count}
                                };
                                hierarchy.push_back(newNode);
                                parent_id = id;
                                id++;
                            }
                        }
                    }
                }
            }
            else if (secondDimension == "TimeInterval") {
                for (const auto& visit : visits) {
                    // Проверка наличия поля "URL" в текущем узле
                    if (visit.find("URL") != visit.end()) {
                        // Извлечение значения поля "URL"
                        std::string url = visit["URL"].get<std::string>();

                        std::string timeValue = visit.at("Time").get<std::string>();

                        std::istringstream timeStream(timeValue);
                        std::tm tm = {};
                        std::istringstream ss(timeValue);
                        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

                        // Выдергиваем часы и минуты
                        int hours = tm.tm_hour;
                        int minutes = tm.tm_min;

                        // Добавляем одну минуту
                        auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                        auto timePointPlusOneMinute = timePoint + std::chrono::minutes(1);

                        // Преобразование обратно в std::tm
                        std::time_t timeT = std::chrono::system_clock::to_time_t(timePointPlusOneMinute);
                        std::tm tmPlusOneMinute = *std::localtime(&timeT);

                        // Выдергиваем обновленные часы и минуты
                        int hoursPlusOneMinute = tmPlusOneMinute.tm_hour;
                        int minutesPlusOneMinute = tmPlusOneMinute.tm_min;

                        // Запись интервала
                        std::ostringstream resultStringStream;
                        resultStringStream << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes
                            << "-" << std::setfill('0') << std::setw(2) << hoursPlusOneMinute << ":" << std::setw(2) << minutesPlusOneMinute;

                        // Проходим по всему массиву hierarchy
                        bool found = false;
                        for (auto& node : hierarchy) {
                            // Проверяем, имеет ли у текущей записи поля "URL", "TimeInterval"
                            if (node.find("URL") != node.end() && !node["URL"].is_null() &&
                                node.find("TimeInterval") != node.end() && !node["TimeInterval"].is_null()) {

                                std::string timeInterval = node.at("TimeInterval").get<std::string>();

                                // Находим позицию тире ("-") в строке
                                size_t dashPosition = timeInterval.find('-');
                                int startHours = 0, startMinutes = 0, endHours = 0, endMinutes = 0;

                                if (dashPosition != std::string::npos) {
                                    // Получаем начальное и конечное время
                                    std::string startTime = timeInterval.substr(0, dashPosition);
                                    std::string endTime = timeInterval.substr(dashPosition + 1);

                                    // Находим позицию двоеточия (":") в начальном времени
                                    size_t colonPositionStart = startTime.find(':');

                                    if (colonPositionStart != std::string::npos) {
                                        // Выделяем часы и минуты из начального времени
                                        std::string startHoursStr = startTime.substr(0, colonPositionStart);
                                        std::string startMinutesStr = startTime.substr(colonPositionStart + 1);

                                        // Преобразуем строки в числа
                                        startHours = std::stoi(startHoursStr);
                                        startMinutes = std::stoi(startMinutesStr);
                                    }

                                    // Находим позицию двоеточия (":") в конечном времени
                                    size_t colonPositionEnd = endTime.find(':');

                                    if (colonPositionEnd != std::string::npos) {
                                        // Выделяем часы и минуты из конечного времени
                                        std::string endHoursStr = endTime.substr(0, colonPositionEnd);
                                        std::string endMinutesStr = endTime.substr(colonPositionEnd + 1);

                                        // Преобразуем строки в числа
                                        endHours = std::stoi(endHoursStr);
                                        endMinutes = std::stoi(endMinutesStr);
                                    }
                                }
                                // Проверяем, совпадает ли URL и диапазон времени
                                if (node["URL"] == url && minutes >= startMinutes && minutes < endMinutes && hours >= startHours && hours <= endHours) {
                                    // Увеличиваем count на 1
                                    node["Count"] = node["Count"].get<int>() + 1;
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if (found == false) {
                            // Если URL не был найден в существующих записях, добавляем новую запись
                            nlohmann::json newNode = {
                                {"Id", id},
                                {"Pid", parent_id},
                                {"URL", url},
                                {"TimeInterval", resultStringStream.str()},
                                {"Count", 1}
                            };
                            hierarchy.push_back(newNode);
                            parent_id = id;
                            id++;
                        }
                    }
                }
            }
            else {
                for (const auto& visit : visits) {
                    // Проверка наличия поля "URL" в текущем узле
                    if (visit.find("URL") != visit.end()) {
                        // Извлечение значения поля "URL"
                        std::string url = visit["URL"].get<std::string>();

                        // Проходим по всему массиву hierarchy
                        bool found = false;
                        for (auto& node : hierarchy) {
                            // Проверяем, имеет ли у текущей записи поля "URL", "TimeInterval"
                            if (node.find("URL") != node.end() && !node["URL"].is_null()) {
                                // Проверяем, совпадает ли URL, IP и диапазон времени
                                if (node["URL"] == url) {
                                    // Увеличиваем count на 1
                                    node["Count"] = node["Count"].get<int>() + 1;
                                    found = true;
                                    break;
                                }
                            }
                        }
                        if (found == false) {
                            // Если URL не был найден в существующих записях, добавляем новую запись
                            nlohmann::json newNode = {
                                {"Id", id},
                                {"Pid", parent_id},
                                {"URL", url},
                                {"Count", count}
                            };
                            hierarchy.push_back(newNode);
                            parent_id = id;
                            id++;
                        }
                    }
                }
            }
        }
        else if (firstDimension == "SourceIP") {
            if (secondDimension == "TimeInterval") {
                for (const auto& visit : visits) {
                    std::string sourceIP = visit.at("SourceIP").get<std::string>();
                    std::string timeValue = visit.at("Time").get<std::string>();

                    std::istringstream timeStream(timeValue);
                    std::tm tm = {};
                    std::istringstream ss(timeValue);
                    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

                    // Выдергиваем часы и минуты
                    int hours = tm.tm_hour;
                    int minutes = tm.tm_min;

                    // Добавляем одну минуту
                    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                    auto timePointPlusOneMinute = timePoint + std::chrono::minutes(1);

                    // Преобразование обратно в std::tm
                    std::time_t timeT = std::chrono::system_clock::to_time_t(timePointPlusOneMinute);
                    std::tm tmPlusOneMinute = *std::localtime(&timeT);

                    // Выдергиваем обновленные часы и минуты
                    int hoursPlusOneMinute = tmPlusOneMinute.tm_hour;
                    int minutesPlusOneMinute = tmPlusOneMinute.tm_min;

                    // Запись интервала
                    std::ostringstream resultStringStream;
                    resultStringStream << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes
                        << "-" << std::setfill('0') << std::setw(2) << hoursPlusOneMinute << ":" << std::setw(2) << minutesPlusOneMinute;

                    // Проходим по всему массиву hierarchy
                    bool found = false;
                    for (auto& node : hierarchy) {
                        if (node.find("SourceIP") != node.end() && !node["SourceIP"].is_null() &&
                            node.find("TimeInterval") != node.end() && !node["TimeInterval"].is_null()) {

                            std::string timeInterval = node.at("TimeInterval").get<std::string>();

                            // Находим позицию тире ("-") в строке
                            size_t dashPosition = timeInterval.find('-');
                            int startHours = 0, startMinutes = 0, endHours = 0, endMinutes = 0;

                            if (dashPosition != std::string::npos) {
                                // Получаем начальное и конечное время
                                std::string startTime = timeInterval.substr(0, dashPosition);
                                std::string endTime = timeInterval.substr(dashPosition + 1);

                                // Находим позицию двоеточия (":") в начальном времени
                                size_t colonPositionStart = startTime.find(':');

                                if (colonPositionStart != std::string::npos) {
                                    // Выделяем часы и минуты из начального времени
                                    std::string startHoursStr = startTime.substr(0, colonPositionStart);
                                    std::string startMinutesStr = startTime.substr(colonPositionStart + 1);

                                    // Преобразуем строки в числа
                                    startHours = std::stoi(startHoursStr);
                                    startMinutes = std::stoi(startMinutesStr);
                                }

                                // Находим позицию двоеточия (":") в конечном времени
                                size_t colonPositionEnd = endTime.find(':');

                                if (colonPositionEnd != std::string::npos) {
                                    // Выделяем часы и минуты из конечного времени
                                    std::string endHoursStr = endTime.substr(0, colonPositionEnd);
                                    std::string endMinutesStr = endTime.substr(colonPositionEnd + 1);

                                    // Преобразуем строки в числа
                                    endHours = std::stoi(endHoursStr);
                                    endMinutes = std::stoi(endMinutesStr);
                                }
                                // Проверяем, совпадает ли IP и диапазон времени
                                if (node["SourceIP"].get<std::string>() == sourceIP && minutes >= startMinutes && minutes < endMinutes && hours >= startHours && hours <= endHours) {
                                    // Увеличиваем count на 1
                                    node["Count"] = node["Count"].get<int>() + 1;
                                    found = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (found == false) {
                        // Если URL не был найден в существующих записях, добавляем новую запись
                        nlohmann::json newNode = {
                            {"Id", id},
                            {"Pid", parent_id},
                            {"SourceIP", sourceIP},
                            {"TimeInterval", resultStringStream.str()},
                            {"Count", 1}
                        };
                        hierarchy.push_back(newNode);
                        parent_id = id;
                        id++;
                    }
                }
            }
            else {
                for (const auto& visit : visits) {
                    std::string sourceIP = visit.at("SourceIP").get<std::string>();

                    // Проходим по всему массиву hierarchy
                    bool found = false;
                    for (auto& node : hierarchy) {
                        if (node.find("SourceIP") != node.end() && !node["SourceIP"].is_null()) {
                            // Проверяем, совпадает ли IP и диапазон времени
                            if (node["SourceIP"].get<std::string>() == sourceIP) {
                                // Увеличиваем count на 1
                                node["Count"] = node["Count"].get<int>() + 1;
                                found = true;
                                break;
                            }
                        }
                    }
                    if (found == false) {
                        // Если URL не был найден в существующих записях, добавляем новую запись
                        nlohmann::json newNode = {
                            {"Id", id},
                            {"Pid", parent_id},
                            {"SourceIP", sourceIP},
                            {"Count", 1}
                        };
                        hierarchy.push_back(newNode);
                        parent_id = id;
                        id++;
                    }
                }
            }
        }
        else if (firstDimension == "TimeInterval") {
            for (const auto& visit : visits) {
                std::string timeValue = visit.at("Time").get<std::string>();

                std::istringstream timeStream(timeValue);
                std::tm tm = {};
                std::istringstream ss(timeValue);
                ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

                // Выдергиваем часы и минуты
                int hours = tm.tm_hour;
                int minutes = tm.tm_min;

                // Добавляем одну минуту
                auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                auto timePointPlusOneMinute = timePoint + std::chrono::minutes(1);

                // Преобразование обратно в std::tm
                std::time_t timeT = std::chrono::system_clock::to_time_t(timePointPlusOneMinute);
                std::tm tmPlusOneMinute = *std::localtime(&timeT);

                // Выдергиваем обновленные часы и минуты
                int hoursPlusOneMinute = tmPlusOneMinute.tm_hour;
                int minutesPlusOneMinute = tmPlusOneMinute.tm_min;

                // Запись интервала
                std::ostringstream resultStringStream;
                resultStringStream << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes
                    << "-" << std::setfill('0') << std::setw(2) << hoursPlusOneMinute << ":" << std::setw(2) << minutesPlusOneMinute;

                // Проходим по всему массиву hierarchy
                bool found = false;
                for (auto& node : hierarchy) {
                    if (node.find("TimeInterval") != node.end() && !node["TimeInterval"].is_null()) {

                        std::string timeInterval = node.at("TimeInterval").get<std::string>();

                        // Находим позицию тире ("-") в строке
                        size_t dashPosition = timeInterval.find('-');
                        int startHours = 0, startMinutes = 0, endHours = 0, endMinutes = 0;

                        if (dashPosition != std::string::npos) {
                            // Получаем начальное и конечное время
                            std::string startTime = timeInterval.substr(0, dashPosition);
                            std::string endTime = timeInterval.substr(dashPosition + 1);

                            // Находим позицию двоеточия (":") в начальном времени
                            size_t colonPositionStart = startTime.find(':');

                            if (colonPositionStart != std::string::npos) {
                                // Выделяем часы и минуты из начального времени
                                std::string startHoursStr = startTime.substr(0, colonPositionStart);
                                std::string startMinutesStr = startTime.substr(colonPositionStart + 1);

                                // Преобразуем строки в числа
                                startHours = std::stoi(startHoursStr);
                                startMinutes = std::stoi(startMinutesStr);
                            }

                            // Находим позицию двоеточия (":") в конечном времени
                            size_t colonPositionEnd = endTime.find(':');

                            if (colonPositionEnd != std::string::npos) {
                                // Выделяем часы и минуты из конечного времени
                                std::string endHoursStr = endTime.substr(0, colonPositionEnd);
                                std::string endMinutesStr = endTime.substr(colonPositionEnd + 1);

                                // Преобразуем строки в числа
                                endHours = std::stoi(endHoursStr);
                                endMinutes = std::stoi(endMinutesStr);
                            }
                            // Проверяем, совпадает ли IP и диапазон времени
                            if (minutes >= startMinutes && minutes < endMinutes && hours >= startHours && hours <= endHours) {
                                // Увеличиваем count на 1
                                node["Count"] = node["Count"].get<int>() + 1;
                                found = true;
                                break;
                            }
                        }
                    }
                }
                if (found == false) {
                    // Если URL не был найден в существующих записях, добавляем новую запись
                    nlohmann::json newNode = {
                        {"Id", id},
                        {"Pid", parent_id},
                        {"TimeInterval", resultStringStream.str()},
                        {"Count", 1}
                    };
                    hierarchy.push_back(newNode);
                    parent_id = id;
                    id++;
                }
            }
        }
    }
    void queryProcessing(SOCKET client_socket) {
        std::string argv[7];
        char buffer[1024];
        int bytesReceived = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytesReceived == SOCKET_ERROR) {
            int error = WSAGetLastError();
            if (error == WSAEWOULDBLOCK || error == WSAECONNRESET) {
                std::cerr << "Ошибка при получении данных от клиента: " << error << std::endl;
                closesocket(client_socket);
                return;
            }
            std::cerr << "Другая ошибка при получении данных от клиента: " << error << std::endl;
            closesocket(client_socket);
            return;
        }

        if (bytesReceived == 0) {
            std::cout << "Соединение закрыто клиентом." << std::endl;
            closesocket(client_socket);
            return;
        }

        buffer[bytesReceived] = '\0';
        std::cout << "connect OK\n";
        std::cout << "Client answer: " << buffer << std::endl;
        int argc = 0;
        std::istringstream iss(buffer);

        std::string token;

        while (iss >> token) {
            argv[argc] = token;
            argc++;
        }

        // Запрос от from_link_shortener или от collecting_statistics
        if (argv[2] == "from_link_shortener") {
            std::unique_lock<std::mutex> lock(dbMutex);
            const std::string filename = "C:\\links.txt";
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cout << "File opening error.\n";
                return;
            }

            HashTable hashTable;
            hashTable.count = 0;
            copyingValuesFromFile(file, hashTable);
            HSET(hashTable, argv[0], argv[1]);
            fileUpdate(filename, hashTable);

            file.close();
        }
        // ip_address redirected_url from_collecting_statistics timestamp"
        else if (argv[2] == "from_collecting_statistics") {
            std::unique_lock<std::mutex> lock(jsonMutex);

            // Разбиваем строку на аргументы
            std::string ip_address = argv[0];
            std::string redirected_url = argv[1];
            std::string timestamp = argv[3] + " " + argv[4];

            const std::string json_filename = "C:\\visits.json";

            // Пытаемся открыть существующий файл
            std::ifstream existing_json_file(json_filename);
            nlohmann::json existing_json_data;

            // Если файл существует и не пуст, загружаем его содержимое
            if (existing_json_file.is_open() && existing_json_file.peek() != std::ifstream::traits_type::eof()) {
                existing_json_file >> existing_json_data;
                existing_json_file.close();
            }

            // Создаем новый объект для новой записи
            nlohmann::json new_entry;
            new_entry["SourceIP"] = ip_address;
            new_entry["URL"] = redirected_url;
            new_entry["Time"] = timestamp;

            // Добавляем новую запись к массиву
            existing_json_data["visits"].push_back(new_entry);

            // Сохраняем обновленные данные обратно в файл
            std::ofstream json_file(json_filename);
            json_file << std::setw(4) << existing_json_data << std::endl;  // Для форматированного вывода
            json_file.close();
        }
        else if (argv[0] == "Dimensions") {
            const std::string jsonFilename = "C:\\visits.json";
            const std::string reportFilename = "C:\\report.json";

            std::ifstream jsonFile(jsonFilename);
            if (!jsonFile.is_open()) {
                std::cerr << "Failed to open visits.json" << std::endl;
                return;
            }
            nlohmann::json visits;
            jsonFile >> visits;
            jsonFile.close();

            nlohmann::json hierarchy = nlohmann::json::array();
            generateHierarchy(visits["visits"], hierarchy, argv[1], argv[2], argv[3]);

            std::ofstream reportFile(reportFilename);
            if (!reportFile.is_open()) {
                std::cerr << "Failed to open report.json" << std::endl;
                return;
            }
            reportFile << std::setw(4) << hierarchy << std::endl;
            reportFile.close();

            // Открытие файла
            std::ifstream file(reportFilename);
            if (!file.is_open()) {
                std::cerr << "Failed to open report.json" << std::endl;
                return;
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();

            // Десериализация JSON-данных в строку
            nlohmann::json jsonData = nlohmann::json::parse(buffer.str());
            std::string jsonString = jsonData.dump();

            // Отправка данных по сокету
            int bytesSent = send(client_socket, jsonString.c_str(), jsonString.length(), 0);
            if (bytesSent == SOCKET_ERROR) {
                std::cerr << "Failed to send data." << std::endl;
            }
            else {
                std::cout << "Data sent successfully." << std::endl;
            }
        }
    }
};



DWORD WINAPI threadFunction(LPVOID lpParam) {
    SOCKET client_socket = (SOCKET)lpParam;
    Server server(client_socket);
    return 0;
}

int main() {
    setlocale(LC_ALL, "Rus");
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(6379);

    bind(s, (SOCKADDR*)&server, sizeof(server));
    listen(s, 100);

    SOCKET client_socket;
    SOCKADDR_IN client_addr;
    int client_addr_size = sizeof(client_addr);
    std::cout << "Waiting for connection...\n";
    while (client_socket = accept(s, (SOCKADDR*)&client_addr, &client_addr_size)) {
        HANDLE thread = CreateThread(NULL, 0, threadFunction, (LPVOID)client_socket, NULL, 0);
        if (thread == NULL) {
            std::cout << "Thread creation failed\n";
            return -1;
        }
        CloseHandle(thread);
    }

    closesocket(s);
    WSACleanup();
    return 0;
}

void HSET(HashTable& hashtable, std::string& key, std::string& value) {
    if (hashtable.count < SIZE) {
        int index = firstHash(key);
        int step = secondHash(key);
        if (hashtable.keys[index].empty()) {
            hashtable.keys[index] = key;
            hashtable.values[index] = value;
        }
        else if (hashtable.keys[index] != key) {
            while (!hashtable.keys[index].empty()) {
                index = (index + step) % SIZE;
            }
            hashtable.keys[index] = key;
            hashtable.values[index] = value;
        }
        else {
            std::cout << "Key already exists.\n";
        }
    }
    else {
        std::cout << "HashTable is full.\n";
    }
}
