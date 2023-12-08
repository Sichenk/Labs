#pragma once
#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <nlohmann/json.hpp>

using namespace std;

#define SIZE 901

class Array {
private:
	string elements[SIZE];
	int count;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& count;
        for (int i = 0; i < count; ++i) {
            ar& elements[i];
        }
    }

public:
	Array() : count(0) {}

	void AADD(string& value);

	void AREM(int& index);

	int AISMEMBER(int& index);

	string AGET(int& index);

	void AOVERWRITE(int& index, string& value);

    // Сериализация в бинарный формат
    void serializeBinary(const string& filename) {
        ofstream ofs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_oarchive ar(ofs);
        ar << *this;
    }

    // Десериализация из бинарного формата
    void deserializeBinary(const string& filename) {
        ifstream ifs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_iarchive ar(ifs);
        ar >> *this;
    }

    // Сериализация в текстовый формат JSON
    void serializeJSON(const string& filename) const {
        nlohmann::json j;
        j["count"] = count;
        for (int i = 0; i < count; ++i) {
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
        count = j["count"];
        auto jsonElements = j["elements"];
        for (int i = 0; i < count; ++i) {
            elements[i] = jsonElements[i];
        }
    }

    void printElements() {
        for (int i = 0; i < count; ++i) {
            cout << "Element " << i << ": " << elements[i] << endl;
        }
    }
};