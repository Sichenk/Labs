#pragma once
#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <nlohmann/json.hpp>

using namespace std;

#define SIZE 901

class DoubleNode {
public:
	string data;
	class DoubleNode* next;
	class DoubleNode* prev;
	DoubleNode(string value, DoubleNode* head, DoubleNode* tail) : data(value), next(head), prev(tail) {}
    DoubleNode() : next(nullptr), prev(nullptr) {}

private:
	friend class boost::serialization::access;

	template <class Archive>
	void serialize(Archive& dll, const unsigned int version) {
		dll& data;
		dll& next;
		dll& prev;
	}
};

class DoublyLinkedList {
private:
	DoubleNode* head;
	DoubleNode* tail;

    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& dll, const unsigned int version) {
        dll& head;
    }

public:
	DoublyLinkedList() : head(nullptr), tail(nullptr) {}

	void DLLADD(string& value);

	string DLLPOP();

	void DLLREM(string& value);

	int DLLISMEMBER(string& value);

	void DLLADDTOEND(string& value);

	string DLLPOPEND();

	void DLLPR();

    // Бинарная сериализация
    void serializeBinary(const string& filename) const {
        ofstream ofs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_oarchive dll(ofs);
        dll << *this;
    }

    // Бинарная десериализация
    void deserializeBinary(const string& filename) {
        ifstream ifs("C:\\Users\\Никита Сильченко\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_iarchive dll(ifs);
        dll >> *this;
    }

    // Сериализация в текстовый формат JSON
    void serializeJSON(const string& filename) const {
        nlohmann::json j;
        DoubleNode* current = tail;
        while (current != nullptr) {
            j["nodes"].push_back({ {"data", current->data} });
            current = current->prev;
        }
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
            DLLADD(data);
        }
    }

    void clearList() {
        while (head != nullptr) {
            DoubleNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
