#pragma once
#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <nlohmann/json.hpp>

using namespace std;

#define SIZE 901

class Node {
public:
    string data;
    class Node* next;
    Node(string value, Node* head) : data(value), next(head) {}
    Node() : next(nullptr) {}

private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& sll, const unsigned int version) {
        sll& data;
        sll &next;
    }
};

class SinglyLinkedList {
private:
    Node* head;

    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& sll, const unsigned int version) {
        sll& head;
    }

public:
    SinglyLinkedList() : head(nullptr) {}

    void SLLADD(string& value);

    string SLLPOP();

    void SLLREM(string& value);

    int SLLISMEMBER(string& value);

    void SLLPR();

    // Бинарная сериализация
    void serializeBinary(const string& filename) const {
        ofstream ofs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_oarchive sll(ofs);
        sll << *this;
    }

    // Бинарная десериализация
    void deserializeBinary(const string& filename) {
        ifstream ifs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_iarchive sll(ifs);
        sll >> *this;
    }

    // Сериализация в текстовый формат JSON
    void serializeJSON(const string& filename) const {
        nlohmann::json j;
        Node* current = head;
        while (current != nullptr) {
            j["nodes"].push_back({ {"data", current->data} });
            current = current->next;
        }
        reverse(j["nodes"].begin(), j["nodes"].end());
        ofstream ofs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename);
        ofs << j.dump(4);
    }

    // Десериализация из текстового формата JSON
    void deserializeJSON(const string& filename) {
        ifstream ifs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename);
        nlohmann::json j;
        ifs >> j;

        clearList();

        for (const auto& node : j["nodes"]) {
            string data = node["data"];
            SLLADD(data);
        }
    }

    void clearList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};