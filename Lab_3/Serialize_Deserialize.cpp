#include "array.h"
#include "singly_linked_list.h"
#include "doubly_linked_list.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "binary_search_tree.h"

int main() {
    Array array;

    string a_value1 = "ArrayValue1";
    string a_value2 = "ArrayValue2";

    array.AADD(a_value1);
    array.AADD(a_value2);

    // Сериализация в бинарный формат
    array.serializeBinary("array_binary.dat");

    // Десериализация из бинарного формата
    cout << "Array" << endl;
    Array loadedArray;
    loadedArray.deserializeBinary("array_binary.dat");
    cout << "Binary Format:" << endl;
    loadedArray.printElements();

    // Сериализация в текстовый формат JSON
    array.serializeJSON("array_txt.json");

    // Десериализация из текстового формата JSON
    Array loadedArrayJSON;
    loadedArrayJSON.deserializeJSON("array_txt.json");
    cout << "Text Format:" << endl;
    loadedArrayJSON.printElements();
    cout << endl;

    //-------------------------------------------------------
    SinglyLinkedList list;

    // Добавление элементов в список
    string sll_value1 = "SLLValue1";
    string sll_value2 = "SLLValue2";
    string sll_value3 = "SLLValue3";

    list.SLLADD(sll_value1);
    list.SLLADD(sll_value2);
    list.SLLADD(sll_value3);

    // Сериализация в бинарный формат
    list.serializeBinary("sll_binary.dat");

    // Десериализация из бинарного формата
    cout << "Singly Linked List" << endl;
    SinglyLinkedList loadedList;
    loadedList.deserializeBinary("sll_binary.dat");
    cout << "Binary Format:" << endl;
    loadedList.SLLPR();

    // Сериализация в текстовый формат JSON
    list.serializeJSON("sll_txt.json");
    list.clearList();

    // Десериализация из текстового формата JSON
    SinglyLinkedList loadedListJSON;
    loadedListJSON.deserializeJSON("sll_txt.json");
    cout << "Text Format:" << endl;
    loadedListJSON.SLLPR();
    cout << endl;

    //-------------------------------------------------------
    DoublyLinkedList doubly_list;

    // Добавление элементов в список
    string dll_value1 = "DLLValue1";
    string dll_value2 = "DLLValue2";
    string dll_value3 = "DLLValue3";

    doubly_list.DLLADD(dll_value1);
    doubly_list.DLLADD(dll_value2);
    doubly_list.DLLADD(dll_value3);

    // Сериализация в бинарный формат
    doubly_list.serializeBinary("dll_binary.dat");

    // Десериализация из бинарного формата
    cout << "Doubly Linked List" << endl;
    DoublyLinkedList loadedDoublyList;
    loadedDoublyList.deserializeBinary("dll_binary.dat");
    cout << "Binary Format:" << endl;
    loadedDoublyList.DLLPR();

    // Сериализация в текстовый формат JSON
    doubly_list.serializeJSON("dll_txt.json");
    doubly_list.clearList();

    // Десериализация из текстового формата JSON
    DoublyLinkedList loadedDoublyListJSON;
    loadedDoublyListJSON.deserializeJSON("dll_txt.json");
    cout << "Text Format:" << endl;
    loadedDoublyListJSON.DLLPR();
    cout << endl;

    //-------------------------------------------------------
    Stack stack;

    string st_value1 = "StackValue1";
    string st_value2 = "StackValue2";

    stack.SPUSH(st_value1);
    stack.SPUSH(st_value2);

    // Сериализация в бинарный формат
    stack.serializeBinary("stack_binary.dat");

    // Десериализация из бинарного формата
    cout << "Stack" << endl;
    Stack loadedStack;
    loadedStack.deserializeBinary("stack_binary.dat");
    cout << "Binary Format:" << endl;
    loadedStack.printElements();

    // Сериализация в текстовый формат JSON
    stack.serializeJSON("stack_txt.json");

    // Десериализация из текстового формата JSON
    Stack loadedStackJSON;
    loadedStackJSON.deserializeJSON("stack_txt.json");
    cout << "Text Format:" << endl;
    loadedStackJSON.printElements();
    cout << endl;

    //-------------------------------------------------------
    Queue queue;

    string qu_value1 = "QueueValue1";
    string qu_value2 = "QueueValue2";

    queue.QPUSH(qu_value1);
    queue.QPUSH(qu_value2);

    // Сериализация в бинарный формат
    queue.serializeBinary("queue_binary.dat");

    // Десериализация из бинарного формата
    cout << "Queue" << endl;
    Queue loadedQueue;
    loadedQueue.deserializeBinary("queue_binary.dat");
    cout << "Binary Format:" << endl;
    loadedQueue.printElements();

    // Сериализация в текстовый формат JSON
    queue.serializeJSON("queue_txt.json");

    // Десериализация из текстового формата JSON
    Queue loadedQueueJSON;
    loadedQueueJSON.deserializeJSON("queue_txt.json");
    cout << "Text Format:" << endl;
    loadedQueueJSON.printElements();
    cout << endl;

    //-------------------------------------------------------
    HashTable hashTable;

    string ht_value1 = "HashTableValue1";
    string ht_key1 = "HashTableKey1";

    string ht_value2 = "HashTableValue2";
    string ht_key2 = "HashTableKey2";

    hashTable.HSET(ht_key1, ht_value1);
    hashTable.HSET(ht_key2, ht_value2);

    // Сериализация в бинарный формат
    hashTable.serializeBinary(hashTable, "hashTable_binary.dat");

    // Десериализация из бинарного формата
    cout << "Hash Table" << endl;
    HashTable loadedHashTableBinary = hashTable.deserializeBinary("hashTable_binary.dat");
    cout << "Binary Format:" << endl;
    loadedHashTableBinary.printElements();

    // Сериализация в текстовый формат JSON
    hashTable.serializeJSON(hashTable, "hashTable_txt.json");

    // Десериализация из текстового формата JSON
    HashTable loadedHashTableJSON = hashTable.deserializeJSON("hashTable_txt.json");
    cout << "Text Format:" << endl;
    loadedHashTableJSON.printElements();
    cout << endl;

    //-------------------------------------------------------
    Tree tree;
    tree.root = tree.TADD(tree.root, 8);
    tree.root = tree.TADD(tree.root, 10);
    tree.root = tree.TADD(tree.root, 3);
    tree.root = tree.TADD(tree.root, 14);
    tree.root = tree.TADD(tree.root, 6);
    tree.root = tree.TADD(tree.root, 1);
    tree.root = tree.TADD(tree.root, 4);
    tree.root = tree.TADD(tree.root, 7);
    tree.root = tree.TADD(tree.root, 13);
    tree.root = tree.TADD(tree.root, 2);

    // Сериализация в бинарный формат
    tree.serializeBinary(tree, "binary_tree.dat");

    // Десериализация из бинарного формата
    Tree loadedTreeBinary = tree.deserializeBinary("binary_tree.dat");
    cout << "Binary Format:" << endl;
    loadedTreeBinary.TPRINT(loadedTreeBinary.root, 0);

    // Сериализация в текстовый формат JSON
    tree.serializeJSON(tree, "binary_tree.json");

    // Десериализация из текстового формата JSON
    Tree loadedTreeJSON = tree.deserializeJSON("binary_tree.json");
    cout << "JSON Format:" << endl;
    loadedTreeJSON.TPRINT(loadedTreeJSON.root, 0);
    return 0;
}