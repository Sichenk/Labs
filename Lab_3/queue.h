#pragma once
#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <nlohmann/json.hpp>

using namespace std;

#define SIZE 901

class Queue {
private:
	string elements[SIZE];
	int front;
	int back;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& qu, const unsigned int version) {
        qu& back;
        for (int i = 0; i < back; ++i) {
            qu& elements[i];
        }
    }

public:
	Queue() : front(0), back(0) {}

	void QPUSH(string& value);

	string QPOP();

    // Сериализация в бинарный формат
    void serializeBinary(const string& filename) {
        ofstream ofs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_oarchive qu(ofs);
        qu << *this;
    }

    // Десериализация из бинарного формата
    void deserializeBinary(const string& filename) {
        ifstream ifs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_iarchive qu(ifs);
        qu >> *this;
    }

    // Сериализация в текстовый формат JSON
    void serializeJSON(const string& filename) const {
        nlohmann::json j;
        j["front"] = front;
        j["back"] = back;
        for (int i = 0; i < back; ++i) {
            j["elements"].push_back(elements[i]);
        }
        ofstream ofs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename);
        ofs << j.dump(4);
    }

    // Десериализация из текстового формата JSON
    void deserializeJSON(const string& filename) {
        ifstream ifs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename);
        nlohmann::json j;
        ifs >> j;
        front = j["front"];
        back = j["back"];
        auto jsonElements = j["elements"];
        for (int i = 0; i < back; ++i) {
            elements[i] = jsonElements[i];
        }
    }

    void printElements() {
        for (int i = 0; i < back; ++i) {
            cout << "Element " << i << ": " << elements[i] << endl;
        }
    }
};

