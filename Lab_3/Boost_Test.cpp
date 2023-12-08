#define BOOST_TEST_MODULE BoostTests
#include <boost/test/included/unit_test.hpp>
#include "array.h"
#include "singly_linked_list.h"
#include "doubly_linked_list.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "binary_search_tree.h"

using namespace std;

BOOST_AUTO_TEST_CASE(ArrayAADD)
{
    // ������������ ������� AADD
    Array array;
    string value = "TestValue";

    // ���������� ��������
    array.AADD(value);
    int index = 0;

    // ��������, ��� ������� �������� �������
    BOOST_TEST(array.AISMEMBER(index) == 1);
    BOOST_TEST(array.AGET(index) == value);

}

BOOST_AUTO_TEST_CASE(ArrayAREM)
{
    // ������������ ������� AREM
    Array array;
    string value = "TestValue";

    // ���������� ��������
    array.AADD(value);

    // �������� ��������
    int index = 0;
    array.AREM(index);

    // ��������, ��� ������� ������ �������
    BOOST_TEST(array.AISMEMBER(index) == 0);
}

BOOST_AUTO_TEST_CASE(ArrayAISMEMBER)
{
    // ������������ ������� AISMEMBER
    Array array;
    string value = "TestValue";

    // ���������� ��������
    array.AADD(value);
    int index = 0;

    // ��������, ��� ������� ������������
    BOOST_TEST(array.AISMEMBER(index) == 1);

    // ��������, ��� ������������� ������� �� ���������
    int nonExistentIndex = 1;
    BOOST_TEST(array.AISMEMBER(nonExistentIndex) == 0);
}

BOOST_AUTO_TEST_CASE(ArrayAGET)
{
    // ������������ ������� AGET
    Array array;
    string value = "TestValue";

    // ���������� ��������
    array.AADD(value);
    int index = 0;

    // ��������� �������� �� �������
    string retrievedValue = array.AGET(index);

    // ��������, ��� ������� ���������� �������
    BOOST_TEST(retrievedValue == value);
}

BOOST_AUTO_TEST_CASE(ArrayAOVERWRITE)
{
    // ������������ ������� AOVERWRITE
    Array array;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ��������
    array.AADD(value1);

    // ���������� ��������
    int index = 0;
    array.AOVERWRITE(index, value2);

    // ��������� �������� �� �������
    string receivedValue = array.AGET(index);

    // ��������, ��� ������� ����������� �������
    BOOST_TEST(receivedValue == value2);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedListSLLADD)
{
    // ������������ ������� SLLADD
    SinglyLinkedList list;
    string value = "TestValue";

    // ���������� ��������
    list.SLLADD(value);

    // ��������, ��� ������� �������� �������
    BOOST_TEST(list.SLLISMEMBER(value) == 1);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedListSLLPOP)
{
    // ������������ ������� SLLPOP
    SinglyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ���������
    list.SLLADD(value1);
    list.SLLADD(value2);

    // ���������� ��������
    string poppedValue = list.SLLPOP();

    // ��������, ��� �������� ���������� �������
    BOOST_TEST(poppedValue == value2);

    // ��������, ��� ������� ������ �� ������
    BOOST_TEST(list.SLLISMEMBER(value2) == 0);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedListSLLREM)
{
    // ������������ ������� SLLREM
    SinglyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";
    string value3 = "TestValue3";

    // ���������� ���������
    list.SLLADD(value1);
    list.SLLADD(value2);
    list.SLLADD(value3);

    // �������� ��������
    string valueToRemove = value2;
    list.SLLREM(valueToRemove);

    // ��������, ��� ������� ������ �������
    BOOST_TEST(list.SLLISMEMBER(valueToRemove) == 0);

    // ��������, ��� ��������� �������� �������� � ������
    BOOST_TEST(list.SLLISMEMBER(value1) == 1);
    BOOST_TEST(list.SLLISMEMBER(value3) == 1);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedListSLLISMEMBER)
{
    // ������������ ������� SLLISMEMBER
    SinglyLinkedList list;
    string value = "TestValue";

    // ���������� ��������
    list.SLLADD(value);

    // ��������, ��� ������� ������������
    BOOST_TEST(list.SLLISMEMBER(value) == 1);

    // ��������, ��� ������������� ������� �� ���������
    string nonExistentValue = "NonExistentValue";
    BOOST_TEST(list.SLLISMEMBER(nonExistentValue) == 0);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedListSLLPR)
{
    // ������������ ������� SLLPR
    SinglyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ���������
    list.SLLADD(value1);
    list.SLLADD(value2);

    // ��������������� ������������ ������
    ostringstream oss;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    // ����� ������
    list.SLLPR();

    // �������������� ������������ ������
    cout.rdbuf(coutBuffer);

    // ��������, ��� ����� ������������� ����������
    string expectedOutput = value2 + " -> " + value1 + " -> NULL\n";
    BOOST_TEST(oss.str() == expectedOutput);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLADD)
{
    // ������������ ������� DLLADD
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ���������
    list.DLLADD(value1);
    list.DLLADD(value2);

    // ��������, ��� �������� ��������� �������
    BOOST_TEST(list.DLLISMEMBER(value1) == 1);
    BOOST_TEST(list.DLLISMEMBER(value2) == 1);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLPOP)
{
    // ������������ ������� DLLPOP
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ���������
    list.DLLADD(value1);
    list.DLLADD(value2);

    // ���������� ��������
    string poppedValue = list.DLLPOP();

    // ��������, ��� �������� ���������� �������
    BOOST_TEST(poppedValue == value2);

    // ��������, ��� ������� ������ �� ������
    BOOST_TEST(list.DLLISMEMBER(value2) == 0);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLREM)
{
    // ������������ ������� DLLREM
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";
    string value3 = "TestValue3";

    // ���������� ���������
    list.DLLADD(value1);
    list.DLLADD(value2);
    list.DLLADD(value3);

    // �������� ��������
    string valueToRemove = value2;
    list.DLLREM(valueToRemove);

    // ��������, ��� ������� ������ �������
    BOOST_TEST(list.DLLISMEMBER(valueToRemove) == 0);

    // ��������, ��� ��������� �������� �������� � ������
    BOOST_TEST(list.DLLISMEMBER(value1) == 1);
    BOOST_TEST(list.DLLISMEMBER(value3) == 1);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLISMEMBER)
{
    // ������������ ������� DLLISMEMBER
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";
    string value3 = "TestValue3";

    // ���������� ���������
    list.DLLADD(value1);
    list.DLLADD(value2);
    list.DLLADD(value3);

    // ��������, ��� �������� ������������
    BOOST_TEST(list.DLLISMEMBER(value1) == 1);
    BOOST_TEST(list.DLLISMEMBER(value2) == 1);
    BOOST_TEST(list.DLLISMEMBER(value3) == 1);

    // ��������, ��� ������������� ������� �� ���������
    string nonExistentValue = "NonExistentValue";
    BOOST_TEST(list.DLLISMEMBER(nonExistentValue) == 0);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLADDTOEND)
{
    // ������������ ������� DLLADDTOEND
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ���������
    list.DLLADD(value1);

    // ���������� �������� � ����� ������
    list.DLLADDTOEND(value2);

    // ��������, ��� ������� �������� �������
    BOOST_TEST(list.DLLISMEMBER(value2) == 1);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLPOPEND)
{
    // ������������ ������� DLLPOPEND
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ���������
    list.DLLADD(value1);
    list.DLLADD(value2);

    // ���������� �������� � �����
    string poppedValue = list.DLLPOPEND();

    // ��������, ��� �������� ���������� �������
    BOOST_TEST(poppedValue == value1);

    // ��������, ��� ������� ������ �� ������
    BOOST_TEST(list.DLLISMEMBER(value1) == 0);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLPR)
{
    // ������������ ������� DLLPR
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";
    string value3 = "TestValue3";

    // ���������� ���������
    list.DLLADD(value1);
    list.DLLADD(value2);
    list.DLLADD(value3);

    // ��������������� ������ � ��������� �����
    ostringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    // ����� ������� DLLPR
    list.DLLPR();

    // �������������� ������
    cout.rdbuf(coutBuffer);

    // ��������, ��� ����� ������������� ����������
    BOOST_TEST(output.str() == "NULL <-> TestValue3 <-> TestValue2 <-> TestValue1 <-> NULL\n");
}

BOOST_AUTO_TEST_CASE(StackSPUSH)
{
    // ������������ ������� SPUSH
    Stack stack;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ��������� � ����
    stack.SPUSH(value1);
    stack.SPUSH(value2);

    // ��������, ��� �������� ��������� � ���������� �������
    BOOST_TEST(stack.SPOP() == value2);
    BOOST_TEST(stack.SPOP() == value1);
}

BOOST_AUTO_TEST_CASE(StackSPOP)
{
    // ������������ ������� SPOP
    Stack stack;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ��������� � ����
    stack.SPUSH(value1);
    stack.SPUSH(value2);

    // �������� ��������� �� �����
    string poppedValue1 = stack.SPOP();
    string poppedValue2 = stack.SPOP();

    // ��������, ��� �������� ������� � ���������� �������
    BOOST_TEST(poppedValue2 == value1);
    BOOST_TEST(poppedValue1 == value2);
}

BOOST_AUTO_TEST_CASE(QueueQPUSH)
{
    // ������������ ������� QPUSH
    Queue queue;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ��������� � �������
    queue.QPUSH(value1);
    queue.QPUSH(value2);

    // ��������, ��� �������� ��������� � ���������� �������
    BOOST_TEST(queue.QPOP() == value1);
    BOOST_TEST(queue.QPOP() == value2);
}

BOOST_AUTO_TEST_CASE(QueueQPOP)
{
    // ������������ ������� QPOP
    Queue queue;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // ���������� ��������� � �������
    queue.QPUSH(value1);
    queue.QPUSH(value2);

    // �������� ��������� �� �������
    string poppedValue1 = queue.QPOP();
    string poppedValue2 = queue.QPOP();

    // ��������, ��� �������� ������� � ���������� �������
    BOOST_TEST(poppedValue1 == value1);
    BOOST_TEST(poppedValue2 == value2);
}

BOOST_AUTO_TEST_CASE(HashTableHSET)
{
    // ������������ ������� HSET
    HashTable hashTable;
    string key1 = "Key1";
    string value1 = "TestValue1";
    string key2 = "Key2";
    string value2 = "TestValue2";

    // ���������� ��������� � ���-�������
    hashTable.HSET(key1, value1);
    hashTable.HSET(key2, value2);

    // ��������, ��� �������� ��������� � ���-�������
    BOOST_TEST(hashTable.HGET(key1) == value1);
    BOOST_TEST(hashTable.HGET(key2) == value2);
}

BOOST_AUTO_TEST_CASE(HashTableHSETdublicateKey)
{
    // ������������ ������� HSET
    HashTable hashTable;
    string key1 = "Key";
    string value1 = "TestValue1";
    string key2 = "Key";
    string value2 = "TestValue2";

    // ���������� ��������� � ���-�������
    hashTable.HSET(key1, value1);
    hashTable.HSET(key2, value2);

    // ��������, ��� �������� ��������� � ���-�������
    BOOST_TEST(hashTable.HGET(key1) == value1);
}

BOOST_AUTO_TEST_CASE(HashTableHDEL)
{
    // ������������ ������� HDEL
    HashTable hashTable;
    string key = "Key";
    string value = "TestValue";

    // ���������� �������� � ���-�������
    hashTable.HSET(key, value);

    // �������� �������� �� ���-�������
    hashTable.HDEL(key);

    // ��������, ��� ������� ������
    BOOST_TEST(hashTable.HGET(key) == "");
}

BOOST_AUTO_TEST_CASE(HashTableHGET)
{
    // ������������ ������� HGET
    HashTable hashTable;
    string key = "Key";
    string value = "TestValue";

    // ���������� �������� � ���-�������
    hashTable.HSET(key, value);

    // ��������� �������� �� ���-�������
    string receivedValue = hashTable.HGET(key);

    // ��������, ��� ������� ���������� �������
    BOOST_TEST(receivedValue == value);
}

BOOST_AUTO_TEST_CASE(BinarySearchTreeTADD)
{
    // ������������ ������� TADD
    Tree tree;
    int value1 = 10;
    int value2 = 5;

    // ���������� ��������� � �������� ������ ������
    tree.root = tree.TADD(tree.root, value1);
    tree.root = tree.TADD(tree.root, value2);

    // ��������, ��� �������� ��������� � ���������� �������
    BOOST_TEST(tree.TISMEMBER(tree.root, value1) != nullptr);
    BOOST_TEST(tree.TISMEMBER(tree.root, value2) != nullptr);
}

BOOST_AUTO_TEST_CASE(BinarySearchTreeTDEL)
{
    // ������������ ������� TDEL
    Tree tree;
    int value = 10;

    // ���������� �������� � �������� ������ ������
    tree.root = tree.TADD(tree.root, value);

    // �������� �������� �� ��������� ������ ������
    tree.root = tree.TDEL(tree.root, value);

    // ��������, ��� ������� ������
    BOOST_TEST(tree.TISMEMBER(tree.root, value) == nullptr);
}

BOOST_AUTO_TEST_CASE(BinarySearchTreeTISMEMBER)
{
    // ������������ ������� TISMEMBER
    Tree tree;
    int value = 10;

    // ���������� �������� � �������� ������ ������
    tree.root = tree.TADD(tree.root, value);

    // ��������, ��� ������� ������������
    BOOST_TEST(tree.TISMEMBER(tree.root, value) != nullptr);

    // ��������, ��� ������������� ������� �� ���������
    BOOST_TEST(tree.TISMEMBER(tree.root, value + 1) == nullptr);
}

BOOST_AUTO_TEST_CASE(BinarySearchTreeTPRINT)
{
    // ��������������� ������ � ��������� �����
    ostringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    // ������������ ������� TPRINT
    Tree tree;
    int value1 = 10;
    int value2 = 5;
    int value3 = 15;

    // ���������� ��������� � �������� ������ ������
    tree.root = tree.TADD(tree.root, value1);
    tree.root = tree.TADD(tree.root, value2);
    tree.root = tree.TADD(tree.root, value3);

    // ����� ������� TPRINT
    tree.TPRINT(tree.root, 0);

    // �������������� ������
    cout.rdbuf(coutBuffer);

    // ��������, ��� ����� ������������� ����������
    string expectedOutput =
        "\t15\n"
        "10\n"
        "\t5\n";
    BOOST_TEST(output.str() == expectedOutput);
}