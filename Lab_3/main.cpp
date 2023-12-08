#include <iostream>
#include <string>
#include "array.h"
#include "singly_linked_list.h"
#include "doubly_linked_list.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "binary_search_tree.h"

using namespace std;

// Массив
void Array::AADD(string& value) {
	if (count < SIZE) {
		elements[count] = value;
		count++;
	}
	else {
		cout << "Array is full." << endl;
	}
}

void Array::AREM(int& index) {
	if (index < 0 || index >= count) {
		cout << "The value for this index is empty." << endl;
		return;
	}
	for (int i = index; i < count - 1; i++) {
		elements[i] = elements[i + 1];
	}
	count--;
}

int Array::AISMEMBER(int& index) {
	if (index < 0 || index >= count) {
		return 0;
	}
	return 1;
}

string Array::AGET(int& index) {
	if (index < 0 || index >= count) {
		return NULL;
	}
	return elements[index];
}

void Array::AOVERWRITE(int& index, string& value) {
	if (index < 0 || index >= count) {
		printf("The index is not within the array!\n");
		return;
	}
	elements[index] = value;
}

// Односвязный список
void SinglyLinkedList::SLLADD(string& value) {
	Node* newNode = new Node{ value, head };
	head = newNode;
}

string SinglyLinkedList::SLLPOP() {
	if (head != nullptr) {
		Node* temp = head;
		head = head->next;
		string deletedValue = temp->data;
		delete temp;
		return deletedValue;
	}
	else {
		return "";
	}
}

void SinglyLinkedList::SLLREM(string& value) {
	if (head == nullptr) {
		return;
	}

	Node* current = head;
	Node* previous = nullptr;

	while (current != nullptr) {
		if (current->data == value) {
			if (previous == nullptr) {
				head = current->next;
			}
			else {
				previous->next = current->next;
			}

			delete current;
			return;
		}

		previous = current;
		current = current->next;
	}
}

int SinglyLinkedList::SLLISMEMBER(string& value) {
	if (head == nullptr) {
		return -1;
	}

	Node* current = head;

	while (current != nullptr) {
		if (current->data == value) {
			return 1;
		}

		current = current->next;
	}

	return 0;
}

void SinglyLinkedList::SLLPR() {
	if (head == nullptr) {
		cout << "List is empty" << endl;
		return;
	}

	Node* current = head;

	while (current != nullptr) {
		cout << current->data << " -> ";
		current = current->next;
	}

	cout << "NULL" << endl;
}

// Двусвязный список
void DoublyLinkedList::DLLADD(string& value) {
	DoubleNode* newNode = new DoubleNode{ value, head, nullptr };
	if (head == nullptr) {
		tail = newNode;
	}
	else {
		head->prev = newNode;
	}
	head = newNode;
}

string DoublyLinkedList::DLLPOP() {
	if (head != nullptr) {
		DoubleNode* temp = head;
		head = head->next;
		if (head == nullptr) {
			tail = nullptr;
		}
		else {
			head->prev = nullptr;
		}
		string deletedValue = temp->data;
		delete temp;
		return deletedValue;
	}
	else {
		return "";
	}
}

void DoublyLinkedList::DLLREM(string& value) {
	if (head == nullptr) {
		return;
	}

	DoubleNode* current = head;
	DoubleNode* next = current->next;
	DoubleNode* previous = current->prev;

	while (current != nullptr) {
		if (current->data == value) {
			if (current == head) {
				head = current->next;
				if (head != nullptr) {
					head->prev = nullptr;
				}
			}
			else {
				previous->next = next;
				if (current == tail) {
					tail = current->prev;
				}
				else {
					next->prev = previous;
				}
			}
			delete current;
			return;
		}
		previous = current;
		current = current->next;
		if (current != nullptr) {
			next = current->next;
		}
	}
}

int DoublyLinkedList::DLLISMEMBER(string& value) {
	if (head == nullptr) {
		return -1;
	}

	DoubleNode* current = head;

	while (current != nullptr) {
		if (current->data == value) {
			return 1;
		}

		current = current->next;
	}

	return 0;
}

void DoublyLinkedList::DLLADDTOEND(string& value) {
	DoubleNode* newNode = new DoubleNode{ value, nullptr, tail };
	if (tail == nullptr) {
		head = newNode;
	}
	else {
		tail->next = newNode;
	}
	tail = newNode;
}

string DoublyLinkedList::DLLPOPEND() {
	if (tail != nullptr) {
		DoubleNode* temp = tail;
		tail = tail->prev;
		if (tail == nullptr) {
			head = nullptr;
		}
		else {
			tail->next = nullptr;
		}
		string deletedValue = temp->data;
		delete temp;
		return deletedValue;
	}
	else {
		return "";
	}
}

void DoublyLinkedList::DLLPR() {
	if (head == nullptr) {
		cout << "List is empty" << endl;
		return;
	}

	DoubleNode* current = head;

	cout << "NULL <-> ";
	while (current != nullptr) {
		cout << current->data << " <-> ";
		current = current->next;
	}

	cout << "NULL" << endl;
}

// Стек
void Stack::SPUSH(string& value) {
	if (top < SIZE - 1) {
		top++;
		elements[top] = value;
	}
	else {
		cout << "Stack is full." << endl;
	}
}

string Stack::SPOP() {
	if (top == -1) {
		cout << "Stack is empty." << endl;
		return "";
	}

	string value = elements[top];
	elements[top] = "";
	top--;
	return value;
}

// Очередь
void Queue::QPUSH(string& value) {
	if (back < SIZE - 1) {
		elements[back] = value;
		back++;
	}
	else {
		cout << "Queue is full." << endl;
	}
}

string Queue::QPOP() {
	if (front == back) {
		cout << "Queue is empty." << endl;
		return "";
	}

	string value = elements[front];
	elements[front] = "";
	front++;
	return value;
}

// Хэш-таблица
void HashTable::HSET(string& key, string& value) {
	if (count < SIZE) {
		int index = hash(key);
		int step = secondHash(key);
		if (keys[index] == "") {
			keys[index] = key;
			values[index] = value;
		}
		else if (keys[index] != key) {
			while (keys[index] != "") {
				index = (index + step) % SIZE;
			}
			keys[index] = key;
			values[index] = value;
		}
		else {
			return;
		}
		count++;
	}
	else {
		cout << "HashTable is full." << endl;
	}
}

void HashTable::HDEL(string& key) {
	int index = hash(key);
	if (keys[index] == "" && values[index] == "") {
		cout << "This cell is already empty." << endl;
	}
	else {
		keys[index] = "";
		values[index] = "";
		count--;
	}
}

string HashTable::HGET(string& key) {
	int index = hash(key);
	if (keys[index] != "" && values[index] != "") {
		return values[index];
	}
	else {
		return "";
	}
}

// Бинарное дерево поиска
TreeNode* Tree::TADD(TreeNode* root, int value) {
	if (root == nullptr) {
		return new TreeNode(value);
	}
	else {
		if (value < root->data) {
			root->left = TADD(root->left, value);
		}
		else if (value > root->data) {
			root->right = TADD(root->right, value);
		}
	}
	return root;
}

TreeNode* Tree::TDEL(TreeNode* root, int value) {
	if (root == nullptr) {
		return root;
	}
	if (value < root->data) {
		root->left = TDEL(root->left, value);
	}
	else if (value > root->data) {
		root->right = TDEL(root->right, value);
	}
	else {
		if (root->left == nullptr) {
			TreeNode* temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == nullptr) {
			TreeNode* temp = root->left;
			delete root;
			return temp;
		}
		TreeNode* temp = root->right;
		while (temp != nullptr && temp->left != nullptr) {
			temp = temp->left;
		}
		root->data = temp->data;
		root->right = TDEL(root->right, temp->data);
	}
	return root;
}

TreeNode* Tree::TISMEMBER(TreeNode* root, int value) {
	if (root == nullptr || value == root->data) {
		return root;
	}
	if (value < root->data) {
		return TISMEMBER(root->left, value);
	}
	return TISMEMBER(root->right, value);
}

void Tree::TPRINT(TreeNode* root, int level) {
	if (root == nullptr) {
		return;
	}
	TPRINT(root->right, level + 1);
	for (int i = 0; i < level; i++) {
		cout << "\t";
	}
	cout << root->data << endl;
	TPRINT(root->left, level + 1);
}

/*int main() {
	Array array;
	SinglyLinkedList singlyLinkedList;
	DoublyLinkedList doublyLinkedList;
	Stack stack;
	Queue queue;
	HashTable hashTable;
	Tree tree;
	int choice = -1;
	cout << "1 - Array" << endl;
	cout << "2 - Singly Linked List" << endl;
	cout << "3 - Doubly Linked List" << endl;
	cout << "4 - Stack" << endl;
	cout << "5 - Queue" << endl;
	cout << "6 - Hashtable" << endl;
	cout << "7 - Binary Search Tree" << endl;
	cout << "0 - Exit" << endl << endl;
	while (choice != 0) {
		cout << "Your choice: ";
		cin >> choice;
		if (choice == 1) {
			string command;
			cout << "Enter the command (AADD/AREM/AISMEMBER/AGET/AOVERWRITE): ";
			cin.ignore();
			getline(cin, command);
			if (command == "AADD") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				array.AADD(value);
				cout << "Done!" << endl;
			}
			else if (command == "AREM") {
				int index;
				cout << "Enter the index: ";
				cin >> index;
				array.AREM(index);
				cout << "Done!" << endl;
			}
			else if (command == "AISMEMBER") {
				int index;
				cout << "Enter the index: ";
				cin >> index;
				cout << array.AISMEMBER(index) << endl;
			}
			else if (command == "AGET") {
				int index;
				cout << "Enter the index: ";
				cin >> index;
				string received_item = array.AGET(index);
				cout << "Received item: " << received_item << endl;
			}
			else if (command == "AOVERWRITE") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				int index;
				cout << "Enter the index: ";
				cin >> index;
				array.AOVERWRITE(index, value);
			}
			else {
				cout << "Invalid command!" << endl;
			}
			command.clear();
		}
		else if (choice == 2) {
			string command;
			cout << "Enter the command (SLLADD/SLLPOP/SLLREM/SLLISMEMBER/SLLPR): ";
			cin.ignore();
			getline(cin, command);
			if (command == "SLLADD") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				singlyLinkedList.SLLADD(value);
				cout << "Done!" << endl;
			}
			if (command == "SLLPOP") {
				string popped_item = singlyLinkedList.SLLPOP();
				cout << "Popped item: " << popped_item << endl;
			}
			else if (command == "SLLREM") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				singlyLinkedList.SLLREM(value);
				cout << "Done!" << endl;
			}
			else if (command == "SLLISMEMBER") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				cout << singlyLinkedList.SLLISMEMBER(value) << endl;
			}
			else if (command == "SLLPR") {
				singlyLinkedList.SLLPR();
			}
			else {
				cout << "Invalid command!" << endl;
			}
			command.clear();
		}
		else if (choice == 3) {
			string command;
			cout << "Enter the command (DLLADD/DLLPOP/DLLREM/DLLISMEMBER/DLLADDTOEND/DLLPOPEND/DLLPR): ";
			cin.ignore();
			getline(cin, command);
			if (command == "DLLADD") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				doublyLinkedList.DLLADD(value);
				cout << "Done!" << endl;
			}
			else if (command == "DLLPOP") {
				string popped_item = doublyLinkedList.DLLPOP();
				cout << "Popped item: " << popped_item << endl;
			}
			else if (command == "DLLREM") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				doublyLinkedList.DLLREM(value);
				cout << "Done!" << endl;
			}
			else if (command == "DLLISMEMBER") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				cout << doublyLinkedList.DLLISMEMBER(value) << endl;
			}
			else if (command == "DLLADDTOEND") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				doublyLinkedList.DLLADDTOEND(value);
				cout << "Done!" << endl;
			}
			else if (command == "DLLPOPEND") {
				string popped_item = doublyLinkedList.DLLPOPEND();
				cout << "Popped item: " << popped_item << endl;
			}
			else if (command == "DLLPR") {
				doublyLinkedList.DLLPR();
			}
			else {
				cout << "Invalid command!" << endl;
			}
			command.clear();
		}
		else if (choice == 4) {
			string command;
			cout << "Enter the command (SPUSH/SPOP): ";
			cin.ignore();
			getline(cin, command);
			if (command == "SPUSH") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				stack.SPUSH(value);
				cout << "Done!" << endl;
			}
			else if (command == "SPOP") {
				string popped_item = stack.SPOP();
				cout << "Popped item: " << popped_item << endl;
			}
		}
		else if (choice == 5) {
			string command;
			cout << "Enter the command (QPUSH/QPOP): ";
			cin.ignore();
			getline(cin, command);
			if (command == "QPUSH") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				queue.QPUSH(value);
				cout << "Done!" << endl;
			}
			else if (command == "QPOP") {
				string popped_item = queue.QPOP();
				cout << "Popped item: " << popped_item << endl;
			}
		}
		else if (choice == 6) {
			string command;
			cout << "Enter the command (HSET/HDEL/HGET): ";
			cin.ignore();
			getline(cin, command);
			if (command == "HSET") {
				string value;
				cout << "Enter the value: ";
				getline(cin, value);
				string key;
				cout << "Enter the key: ";
				getline(cin, key);
				hashTable.HSET(key, value);
				cout << "Done!" << endl;
			}
			else if (command == "HDEL") {
				string key;
				cout << "Enter the key: ";
				getline(cin, key);
				hashTable.HDEL(key);
				cout << "Done!" << endl;
			}
			else if (command == "HGET") {
				string key;
				cout << "Enter the key: ";
				getline(cin, key);
				string received_item = hashTable.HGET(key);
				cout << "Received item: " << received_item << endl;
			}
		}
		else if (choice == 7) {
			string command;
			cout << "Enter the command (TADD/TDEL/TISMEMBER/TPRINT): ";
			cin.ignore();
			getline(cin, command);
			if (command == "TADD") {
				int value;
				cout << "Enter the value: ";
				cin >> value;
				tree.root = tree.TADD(tree.root, value);
				cout << "Done!" << endl;
			}
			else if (command == "TDEL") {
				int value;
				cout << "Enter the value: ";
				cin >> value;
				tree.root = tree.TDEL(tree.root, value);
				cout << "Done!" << endl;
			}
			else if (command == "TISMEMBER") {
				int value;
				cout << "Enter the value: ";
				cin >> value;
				TreeNode* result = tree.TISMEMBER(tree.root, value);
				if (result != nullptr) {
					cout << "TRUE" << endl;
				}
				else {
					cout << "FALSE" << endl;
				}
			}
			else if (command == "TPRINT") {
				tree.TPRINT(tree.root, 0);
			}
		}
		else if (choice == 0) {
			return 1;
		}
		else {
			cout << "Invalid selection" << endl;
		}
	}
}*/