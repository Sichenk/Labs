#pragma once
#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <nlohmann/json.hpp>

using namespace std;

#define SIZE 901

class TreeNode {
public:
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
    TreeNode() : left(nullptr), right(nullptr) {}
    
    friend class boost::serialization::access;

    // �������� ������������ � ��������������
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& data;
        ar& left;
        ar& right;
    }
};

class Tree {
private:

    friend class boost::serialization::access;

    // �������� ������������ � ��������������
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar& root;
    }

public:
	TreeNode* root;

	Tree() : root(nullptr) {}

	TreeNode* TADD(TreeNode* root, int value);

	TreeNode* TDEL(TreeNode* root, int value);

	TreeNode* TISMEMBER(TreeNode* root, int value);

	void TPRINT(TreeNode* root, int level);

    // ������������ � �������� ������
    void serializeBinary(const Tree& tree, const string& filename) {
        ofstream ofs("C:\\Users\\������ ���������\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_oarchive ar(ofs);
        ar << tree;
    }

    // �������������� �� ��������� �������
    Tree deserializeBinary(const string& filename) {
        ifstream ifs("C:\\Users\\������ ���������\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename, ios::binary);
        boost::archive::binary_iarchive ar(ifs);
        Tree tree;
        ar >> tree;
        return tree;
    }

    // ������������ � ��������� ������ JSON
    void serializeJSON(const Tree& tree, const string& filename) {
        nlohmann::json j;
        // �������� ������� serialize ��� ����� ������
        if (tree.root != nullptr) {
            j["root"] = serializeJSONHelper(tree.root);
        }
        else {
            j["root"] = nullptr;
        }
        ofstream ofs("C:\\Users\\������ ���������\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename);
        ofs << j.dump(4);
    }

    // ��������������� ������� ��� ������������ ����� ������
    nlohmann::json serializeJSONHelper(TreeNode* node) {
        nlohmann::json jsonNode;
        jsonNode["data"] = node->data;

        if (node->left != nullptr) {
            jsonNode["left"] = serializeJSONHelper(node->left);
        }
        else {
            jsonNode["left"] = nullptr;
        }

        if (node->right != nullptr) {
            jsonNode["right"] = serializeJSONHelper(node->right);
        }
        else {
            jsonNode["right"] = nullptr;
        }

        return jsonNode;
    }

    // �������������� �� ���������� ������� JSON
    Tree deserializeJSON(const string& filename) {
        ifstream ifs("C:\\Users\\������ ���������\\Desktop\\Boost_test\\SerializeAndDeserialize\\" + filename);
        nlohmann::json j;
        ifs >> j;

        Tree tree;
        // ��������� ������� "root" � JSON � ������� ����� TreeNode
        if (!j["root"].is_null()) {
            tree.root = deserializeJSONHelper(j["root"]);
        }
        else {
            tree.root = nullptr;
        }

        return tree;
    }

    // ��������������� ������� ��� �������������� ����� ������
    TreeNode* deserializeJSONHelper(const nlohmann::json& jsonNode) {
        TreeNode* node = new TreeNode(jsonNode["data"].get<int>());

        if (!jsonNode["left"].is_null()) {
            node->left = deserializeJSONHelper(jsonNode["left"]);
        }
        else {
            node->left = nullptr;
        }

        if (!jsonNode["right"].is_null()) {
            node->right = deserializeJSONHelper(jsonNode["right"]);
        }
        else {
            node->right = nullptr;
        }

        return node;
    }
};
