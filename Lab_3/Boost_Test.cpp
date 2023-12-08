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
    // Тестирование функции AADD
    Array array;
    string value = "TestValue";

    // Добавление элемента
    array.AADD(value);
    int index = 0;

    // Проверка, что элемент добавлен успешно
    BOOST_TEST(array.AISMEMBER(index) == 1);
    BOOST_TEST(array.AGET(index) == value);

}

BOOST_AUTO_TEST_CASE(ArrayAREM)
{
    // Тестирование функции AREM
    Array array;
    string value = "TestValue";

    // Добавление элемента
    array.AADD(value);

    // Удаление элемента
    int index = 0;
    array.AREM(index);

    // Проверка, что элемент удален успешно
    BOOST_TEST(array.AISMEMBER(index) == 0);
}

BOOST_AUTO_TEST_CASE(ArrayAISMEMBER)
{
    // Тестирование функции AISMEMBER
    Array array;
    string value = "TestValue";

    // Добавление элемента
    array.AADD(value);
    int index = 0;

    // Проверка, что элемент присутствует
    BOOST_TEST(array.AISMEMBER(index) == 1);

    // Проверка, что отсутствующий элемент не считается
    int nonExistentIndex = 1;
    BOOST_TEST(array.AISMEMBER(nonExistentIndex) == 0);
}

BOOST_AUTO_TEST_CASE(ArrayAGET)
{
    // Тестирование функции AGET
    Array array;
    string value = "TestValue";

    // Добавление элемента
    array.AADD(value);
    int index = 0;

    // Получение элемента по индексу
    string retrievedValue = array.AGET(index);

    // Проверка, что получен правильный элемент
    BOOST_TEST(retrievedValue == value);
}

BOOST_AUTO_TEST_CASE(ArrayAOVERWRITE)
{
    // Тестирование функции AOVERWRITE
    Array array;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элемента
    array.AADD(value1);

    // Перезапись элемента
    int index = 0;
    array.AOVERWRITE(index, value2);

    // Получение элемента по индексу
    string receivedValue = array.AGET(index);

    // Проверка, что элемент перезаписан успешно
    BOOST_TEST(receivedValue == value2);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedListSLLADD)
{
    // Тестирование функции SLLADD
    SinglyLinkedList list;
    string value = "TestValue";

    // Добавление элемента
    list.SLLADD(value);

    // Проверка, что элемент добавлен успешно
    BOOST_TEST(list.SLLISMEMBER(value) == 1);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedListSLLPOP)
{
    // Тестирование функции SLLPOP
    SinglyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элементов
    list.SLLADD(value1);
    list.SLLADD(value2);

    // Извлечение элемента
    string poppedValue = list.SLLPOP();

    // Проверка, что извлечен правильный элемент
    BOOST_TEST(poppedValue == value2);

    // Проверка, что элемент удален из списка
    BOOST_TEST(list.SLLISMEMBER(value2) == 0);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedListSLLREM)
{
    // Тестирование функции SLLREM
    SinglyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";
    string value3 = "TestValue3";

    // Добавление элементов
    list.SLLADD(value1);
    list.SLLADD(value2);
    list.SLLADD(value3);

    // Удаление элемента
    string valueToRemove = value2;
    list.SLLREM(valueToRemove);

    // Проверка, что элемент удален успешно
    BOOST_TEST(list.SLLISMEMBER(valueToRemove) == 0);

    // Проверка, что остальные элементы остались в списке
    BOOST_TEST(list.SLLISMEMBER(value1) == 1);
    BOOST_TEST(list.SLLISMEMBER(value3) == 1);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedListSLLISMEMBER)
{
    // Тестирование функции SLLISMEMBER
    SinglyLinkedList list;
    string value = "TestValue";

    // Добавление элемента
    list.SLLADD(value);

    // Проверка, что элемент присутствует
    BOOST_TEST(list.SLLISMEMBER(value) == 1);

    // Проверка, что отсутствующий элемент не считается
    string nonExistentValue = "NonExistentValue";
    BOOST_TEST(list.SLLISMEMBER(nonExistentValue) == 0);
}

BOOST_AUTO_TEST_CASE(SinglyLinkedListSLLPR)
{
    // Тестирование функции SLLPR
    SinglyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элементов
    list.SLLADD(value1);
    list.SLLADD(value2);

    // Перенаправление стандартного вывода
    ostringstream oss;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    // Вывод списка
    list.SLLPR();

    // Восстановление стандартного вывода
    cout.rdbuf(coutBuffer);

    // Проверка, что вывод соответствует ожидаемому
    string expectedOutput = value2 + " -> " + value1 + " -> NULL\n";
    BOOST_TEST(oss.str() == expectedOutput);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLADD)
{
    // Тестирование функции DLLADD
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элементов
    list.DLLADD(value1);
    list.DLLADD(value2);

    // Проверка, что элементы добавлены успешно
    BOOST_TEST(list.DLLISMEMBER(value1) == 1);
    BOOST_TEST(list.DLLISMEMBER(value2) == 1);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLPOP)
{
    // Тестирование функции DLLPOP
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элементов
    list.DLLADD(value1);
    list.DLLADD(value2);

    // Извлечение элемента
    string poppedValue = list.DLLPOP();

    // Проверка, что извлечен правильный элемент
    BOOST_TEST(poppedValue == value2);

    // Проверка, что элемент удален из списка
    BOOST_TEST(list.DLLISMEMBER(value2) == 0);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLREM)
{
    // Тестирование функции DLLREM
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";
    string value3 = "TestValue3";

    // Добавление элементов
    list.DLLADD(value1);
    list.DLLADD(value2);
    list.DLLADD(value3);

    // Удаление элемента
    string valueToRemove = value2;
    list.DLLREM(valueToRemove);

    // Проверка, что элемент удален успешно
    BOOST_TEST(list.DLLISMEMBER(valueToRemove) == 0);

    // Проверка, что остальные элементы остались в списке
    BOOST_TEST(list.DLLISMEMBER(value1) == 1);
    BOOST_TEST(list.DLLISMEMBER(value3) == 1);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLISMEMBER)
{
    // Тестирование функции DLLISMEMBER
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";
    string value3 = "TestValue3";

    // Добавление элементов
    list.DLLADD(value1);
    list.DLLADD(value2);
    list.DLLADD(value3);

    // Проверка, что элементы присутствуют
    BOOST_TEST(list.DLLISMEMBER(value1) == 1);
    BOOST_TEST(list.DLLISMEMBER(value2) == 1);
    BOOST_TEST(list.DLLISMEMBER(value3) == 1);

    // Проверка, что отсутствующий элемент не считается
    string nonExistentValue = "NonExistentValue";
    BOOST_TEST(list.DLLISMEMBER(nonExistentValue) == 0);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLADDTOEND)
{
    // Тестирование функции DLLADDTOEND
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элементов
    list.DLLADD(value1);

    // Добавление элемента в конец списка
    list.DLLADDTOEND(value2);

    // Проверка, что элемент добавлен успешно
    BOOST_TEST(list.DLLISMEMBER(value2) == 1);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLPOPEND)
{
    // Тестирование функции DLLPOPEND
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элементов
    list.DLLADD(value1);
    list.DLLADD(value2);

    // Извлечение элемента с конца
    string poppedValue = list.DLLPOPEND();

    // Проверка, что извлечен правильный элемент
    BOOST_TEST(poppedValue == value1);

    // Проверка, что элемент удален из списка
    BOOST_TEST(list.DLLISMEMBER(value1) == 0);
}

BOOST_AUTO_TEST_CASE(DoublyLinkedListDLLPR)
{
    // Тестирование функции DLLPR
    DoublyLinkedList list;
    string value1 = "TestValue1";
    string value2 = "TestValue2";
    string value3 = "TestValue3";

    // Добавление элементов
    list.DLLADD(value1);
    list.DLLADD(value2);
    list.DLLADD(value3);

    // Перенаправление вывода в строковый поток
    ostringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    // Вызов функции DLLPR
    list.DLLPR();

    // Восстановление вывода
    cout.rdbuf(coutBuffer);

    // Проверка, что вывод соответствует ожидаемому
    BOOST_TEST(output.str() == "NULL <-> TestValue3 <-> TestValue2 <-> TestValue1 <-> NULL\n");
}

BOOST_AUTO_TEST_CASE(StackSPUSH)
{
    // Тестирование функции SPUSH
    Stack stack;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элементов в стек
    stack.SPUSH(value1);
    stack.SPUSH(value2);

    // Проверка, что элементы добавлены в правильном порядке
    BOOST_TEST(stack.SPOP() == value2);
    BOOST_TEST(stack.SPOP() == value1);
}

BOOST_AUTO_TEST_CASE(StackSPOP)
{
    // Тестирование функции SPOP
    Stack stack;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элементов в стек
    stack.SPUSH(value1);
    stack.SPUSH(value2);

    // Удаление элементов из стека
    string poppedValue1 = stack.SPOP();
    string poppedValue2 = stack.SPOP();

    // Проверка, что элементы удалены в правильном порядке
    BOOST_TEST(poppedValue2 == value1);
    BOOST_TEST(poppedValue1 == value2);
}

BOOST_AUTO_TEST_CASE(QueueQPUSH)
{
    // Тестирование функции QPUSH
    Queue queue;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элементов в очередь
    queue.QPUSH(value1);
    queue.QPUSH(value2);

    // Проверка, что элементы добавлены в правильном порядке
    BOOST_TEST(queue.QPOP() == value1);
    BOOST_TEST(queue.QPOP() == value2);
}

BOOST_AUTO_TEST_CASE(QueueQPOP)
{
    // Тестирование функции QPOP
    Queue queue;
    string value1 = "TestValue1";
    string value2 = "TestValue2";

    // Добавление элементов в очередь
    queue.QPUSH(value1);
    queue.QPUSH(value2);

    // Удаление элементов из очереди
    string poppedValue1 = queue.QPOP();
    string poppedValue2 = queue.QPOP();

    // Проверка, что элементы удалены в правильном порядке
    BOOST_TEST(poppedValue1 == value1);
    BOOST_TEST(poppedValue2 == value2);
}

BOOST_AUTO_TEST_CASE(HashTableHSET)
{
    // Тестирование функции HSET
    HashTable hashTable;
    string key1 = "Key1";
    string value1 = "TestValue1";
    string key2 = "Key2";
    string value2 = "TestValue2";

    // Добавление элементов в хэш-таблицу
    hashTable.HSET(key1, value1);
    hashTable.HSET(key2, value2);

    // Проверка, что элементы добавлены в хэш-таблицу
    BOOST_TEST(hashTable.HGET(key1) == value1);
    BOOST_TEST(hashTable.HGET(key2) == value2);
}

BOOST_AUTO_TEST_CASE(HashTableHSETdublicateKey)
{
    // Тестирование функции HSET
    HashTable hashTable;
    string key1 = "Key";
    string value1 = "TestValue1";
    string key2 = "Key";
    string value2 = "TestValue2";

    // Добавление элементов в хэш-таблицу
    hashTable.HSET(key1, value1);
    hashTable.HSET(key2, value2);

    // Проверка, что элементы добавлены в хэш-таблицу
    BOOST_TEST(hashTable.HGET(key1) == value1);
}

BOOST_AUTO_TEST_CASE(HashTableHDEL)
{
    // Тестирование функции HDEL
    HashTable hashTable;
    string key = "Key";
    string value = "TestValue";

    // Добавление элемента в хэш-таблицу
    hashTable.HSET(key, value);

    // Удаление элемента из хэш-таблицы
    hashTable.HDEL(key);

    // Проверка, что элемент удален
    BOOST_TEST(hashTable.HGET(key) == "");
}

BOOST_AUTO_TEST_CASE(HashTableHGET)
{
    // Тестирование функции HGET
    HashTable hashTable;
    string key = "Key";
    string value = "TestValue";

    // Добавление элемента в хэш-таблицу
    hashTable.HSET(key, value);

    // Получение элемента из хэш-таблицы
    string receivedValue = hashTable.HGET(key);

    // Проверка, что получен правильный элемент
    BOOST_TEST(receivedValue == value);
}

BOOST_AUTO_TEST_CASE(BinarySearchTreeTADD)
{
    // Тестирование функции TADD
    Tree tree;
    int value1 = 10;
    int value2 = 5;

    // Добавление элементов в бинарное дерево поиска
    tree.root = tree.TADD(tree.root, value1);
    tree.root = tree.TADD(tree.root, value2);

    // Проверка, что элементы добавлены в правильном порядке
    BOOST_TEST(tree.TISMEMBER(tree.root, value1) != nullptr);
    BOOST_TEST(tree.TISMEMBER(tree.root, value2) != nullptr);
}

BOOST_AUTO_TEST_CASE(BinarySearchTreeTDEL)
{
    // Тестирование функции TDEL
    Tree tree;
    int value = 10;

    // Добавление элемента в бинарное дерево поиска
    tree.root = tree.TADD(tree.root, value);

    // Удаление элемента из бинарного дерева поиска
    tree.root = tree.TDEL(tree.root, value);

    // Проверка, что элемент удален
    BOOST_TEST(tree.TISMEMBER(tree.root, value) == nullptr);
}

BOOST_AUTO_TEST_CASE(BinarySearchTreeTISMEMBER)
{
    // Тестирование функции TISMEMBER
    Tree tree;
    int value = 10;

    // Добавление элемента в бинарное дерево поиска
    tree.root = tree.TADD(tree.root, value);

    // Проверка, что элемент присутствует
    BOOST_TEST(tree.TISMEMBER(tree.root, value) != nullptr);

    // Проверка, что отсутствующий элемент не считается
    BOOST_TEST(tree.TISMEMBER(tree.root, value + 1) == nullptr);
}

BOOST_AUTO_TEST_CASE(BinarySearchTreeTPRINT)
{
    // Перенаправление вывода в строковый поток
    ostringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    // Тестирование функции TPRINT
    Tree tree;
    int value1 = 10;
    int value2 = 5;
    int value3 = 15;

    // Добавление элементов в бинарное дерево поиска
    tree.root = tree.TADD(tree.root, value1);
    tree.root = tree.TADD(tree.root, value2);
    tree.root = tree.TADD(tree.root, value3);

    // Вызов функции TPRINT
    tree.TPRINT(tree.root, 0);

    // Восстановление вывода
    cout.rdbuf(coutBuffer);

    // Проверка, что вывод соответствует ожидаемому
    string expectedOutput =
        "\t15\n"
        "10\n"
        "\t5\n";
    BOOST_TEST(output.str() == expectedOutput);
}