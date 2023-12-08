#pragma once
#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <nlohmann/json.hpp>

using namespace std;

#define SIZE 901

class Stack {
private:
	string elements[SIZE];
	int top;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& st, const unsigned int version) {
        st& top;
        for (int i = 0; i <= top; ++i) {
            st& elements[i];
        }
    }

public:
	Stack() : top(-1) {}

	void SPUSH(string& value);

	string SPOP();

    // Сериализация в бинарный формат
    void serializeBinary(const string& filename) {
        ofstream ofs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_oarchive st(ofs);
        st << *this;
    }

    // Десериализация из бинарного формата
    void deserializeBinary(const string& filename) {
        ifstream ifs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_iarchive st(ifs);
        st >> *this;
    }

    // Сериализация в текстовый формат JSON
    void serializeJSON(const string& filename) const {
        nlohmann::json j;
        j["top"] = top;
        for (int i = 0; i <= top; ++i) {
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
        top = j["top"];
        auto jsonElements = j["elements"];
        for (int top_copy = top; top_copy >= 0; --top_copy) {
            elements[top_copy] = jsonElements[top_copy];
        }
    }

    void printElements() {
        for (int i = 0; top >= 0; --top, ++i) {
            cout << "Element " << i << ": " << elements[top] << endl;
        }
    }
};
