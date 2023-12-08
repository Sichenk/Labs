#pragma once
#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <nlohmann/json.hpp>

using namespace std;

#define SIZE 901

class HashTable {
private:
    string keys[SIZE];
    string values[SIZE];
    int count;

    friend class boost::serialization::access;

    // Операции сериализации и десериализации
    template <class Archive>
    void serialize(Archive& ht, const unsigned int version) {
        ht& count;
        for (int i = 0; i < SIZE; ++i) {
            ht& keys[i];
            ht& values[i];
        }
    }

public:
    HashTable() : count(0) {}

    int hash(string key) {
        int h = 0;
        for (char c : key) {
            h = h * 7 + c;
        }
        return h % SIZE;
    }

    int secondHash(string key) {
        return 7 - (hash(key) % 7);
    }

    void HSET(string& key, string& value);

    void HDEL(string& key);

    string HGET(string& key);

    // Сериализация в бинарный формат
    void serializeBinary(const HashTable& hashtable, const string& filename) {
        ofstream ofs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_oarchive ht(ofs);
        ht << hashtable;
    }

    // Десериализация из бинарного формата
    HashTable deserializeBinary(const string& filename) {
        ifstream ifs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_iarchive ht(ifs);
        HashTable hashtable;
        ht >> hashtable;
        return hashtable;
    }

    // Сериализация в текстовый формат JSON
    void serializeJSON(const HashTable& hashtable, const string& filename) {
        nlohmann::json j;
        j["keys"] = nlohmann::json::array();
        j["values"] = nlohmann::json::array();
        for (int i = 0; i < SIZE; ++i) {
            if (!values[i].empty() || !keys[i].empty()) {
                j["keys"].push_back(hashtable.keys[i]);
                j["values"].push_back(hashtable.values[i]);
            }
        }
        j["count"] = hashtable.count;

        ofstream ofs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename);
        ofs << j.dump(4);
    }

    // Десериализация из текстового формата JSON
    HashTable deserializeJSON(const string& filename) {
        ifstream ifs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename);
        nlohmann::json j;
        ifs >> j;

        HashTable hashtable;
        hashtable.count = j["count"];

        auto jsonKeys = j["keys"];
        auto jsonValues = j["values"];

        for (int i = 0; i < hashtable.count; ++i) {
            hashtable.keys[i] = jsonKeys[i];
            hashtable.values[i] = jsonValues[i];
        }

        return hashtable;
    }

    void printElements() {
        for (int i = 0, index = 0; i < SIZE; ++i) {
            if (!values[i].empty() || !keys[i].empty()) {
                cout << "Element " << index << ": " << values[i] << " " << keys[i] << endl;
                ++index;
            }
        }
    }
};
