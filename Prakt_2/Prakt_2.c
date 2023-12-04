#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include <winsock2.h>

#define SIZE 901

HANDLE dbMutex;

typedef struct {
    char* elements[SIZE];
    int count;
} Set;

typedef struct {
    char* elements[SIZE];
    int top;
} Stack;

typedef struct {
    char* elements[SIZE];
    int front;
    int back;
} Queue;

typedef struct {
    char* keys[SIZE];
    char* values[SIZE];
    int count;
} HashTable;

typedef struct {
    SOCKET serverSocket;
    SOCKET clientSocket;
} ThreadArgs;

int hash(char* str) {
    int h = 0;
    while (*str != '\0') {
        h = h * 7 + *str;
        str++;
    }
    return h % SIZE;
}

int secondHash(char* str) {
    return 7 - (hash(str) % 7);
}

// Множество
void SADD(Set* set, char* value, SOCKET* clientSocket);
void SREM(Set* set, char* value, SOCKET* clientSocket);
int SISMEMBER(Set* set, char* value);

// Стек
void SPUSH(Stack* stack, char* value, SOCKET* clientSocket);
char* SPOP(Stack* stack);

// Очередь
void QPUSH(Queue* queue, char* value, SOCKET* clientSocket);
char* QPOP(Queue* queue);

// Хэш-таблица
void HSET(HashTable* hashtable, char* key, char* value, SOCKET* clientSocket);
char* HDEL(HashTable* hashtable, char* key);
char* HGET(HashTable* hashtable, char* key);

void fileUpdate(FILE* file, char* filename, Set* set, Stack* stack, Queue* queue, HashTable* hashTable) {
    fopen_s(&file, filename, "w");
    fputs("SET:\n", file);
    for (int i = 0; i < SIZE; i++) {
        if (set->elements[i] != NULL) {
            fputs(set->elements[i], file);
            fputs("\n", file);
        }
    }
    fputs("STACK:\n", file);
    for (int i = stack->top; i >= 0; i--) {
        fputs(stack->elements[i], file);
        fputs("\n", file);
    }
    fputs("QUEUE:\n", file);
    for (int i = queue->front; i < queue->back; i++) {
        fputs(queue->elements[i], file);
        fputs("\n", file);
    }
    fputs("HASHTABLE:\n", file);
    for (int i = 0; i < SIZE; i++) {
        if (hashTable->values[i] != NULL && hashTable->keys[i] != NULL) {
            fputs(hashTable->keys[i], file);
            fputs("\n", file);
            fputs(hashTable->values[i], file);
            fputs("\n", file);

        }
    }
    fclose(file);
}

void removeNewline(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

void copyingValuesFromFile(FILE* file, Set* set, Stack* stack, Queue* queue, HashTable* hashTable, SOCKET* client_socket) {
    char line[256];
    long set_current_pos = -1, stack_current_pos = -1, queue_current_pos = -1, hashtable_current_pos = -1;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "SET:\n") == 0) {
            set_current_pos = ftell(file);
        }
        else if (strcmp(line, "STACK:\n") == 0) {
            stack_current_pos = ftell(file);
        }
        else if (strcmp(line, "QUEUE:\n") == 0) {
            queue_current_pos = ftell(file);
        }
        else if (strcmp(line, "HASHTABLE:\n") == 0) {
            hashtable_current_pos = ftell(file);
        }
    }
    rewind(file);
    fseek(file, set_current_pos, SEEK_SET);
    while (fgets(line, sizeof(line), file) != NULL && ftell(file) < stack_current_pos) {
        removeNewline(line);
        SADD(set, line, client_socket);
    }
    fseek(file, stack_current_pos, SEEK_SET);
    char stackData[SIZE][256];
    int stackDataIndex = 0;
    while (fgets(line, sizeof(line), file) != NULL && ftell(file) < queue_current_pos) {
        removeNewline(line);
        strcpy_s(stackData[stackDataIndex], sizeof(stackData[stackDataIndex]), line);
        stackDataIndex++;
    }
    for (int i = stackDataIndex - 1; i >= 0; i--) {
        SPUSH(stack, stackData[i], client_socket);
    }
    fseek(file, queue_current_pos, SEEK_SET);
    while (fgets(line, sizeof(line), file) != NULL && ftell(file) < hashtable_current_pos) {
        removeNewline(line);
        QPUSH(queue, line, client_socket);
    }
    fseek(file, hashtable_current_pos, SEEK_SET);
    char* key = NULL;
    while (fgets(line, sizeof(line), file) != NULL && !feof(file)) {
        removeNewline(line);
        removeNewline(line);
        if (key == NULL) {
            key = _strdup(line);
        }
        else {
            char* value = _strdup(line);
            HSET(hashTable, key, value, client_socket);
            free(key);
            key = NULL;
            free(value);
            value = NULL;
        }
    }
    fclose(file);
}
//---------------------------------------------
            // cd C:\Users\Никита Сильченко\source\repos\Prakt_2\x64\Debug
            // Prakt_2 --file C:\data.txt --query SADD item
            // Prakt_2 --file C:\data.txt --query SREM item
            // Prakt_2 --file C:\data.txt --query SISMEMBER item
            // 
            // Prakt_2 --file C:\data.txt --query SPUSH item
            // Prakt_2 --file C:\data.txt --query SPOP
            // 
            // Prakt_2 --file C:\data.txt --query QPUSH item1
            // Prakt_2 --file C:\data.txt --query QPOP
            // 
            // Prakt_2 --file C:\data.txt --query HSET key1 value1
            // Prakt_2 --file C:\data.txt --query HDEL key1
            // Prakt_2 --file C:\data.txt --query HGET key1

void queryProcessing(int argc, char* argv[], SOCKET* client_socket) {
    // Создание мьютекса для безопасного доступа к базе данных
    dbMutex = CreateMutex(NULL, FALSE, NULL);
    if (dbMutex == NULL) {
        printf("Mutex creation error.\n");
        return -1;
    }
    // Ожидание блокировки мьютекса
    WaitForSingleObject(dbMutex, INFINITE);
    // Проверка корректности аргументов командной строки
    if (argc < 4 || strcmp(argv[1], "--file") != 0 || strcmp(argv[3], "--query") != 0) {
        printf("Usage: %s --file <path_to_file> --query <query>\n", argv[0]);
        return -1;
    }
    char* filename = NULL;
    char* query = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            filename = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[i + 1];
            i++;
        }
    }
    if (filename == NULL || query == NULL) {
        printf("Enter the correct arguments.\n");
        return -1;
    }
    FILE* file = NULL;
    fopen_s(&file, filename, "r");
    if (!file) {
        printf("File opening error.\n");
        return -1;
    }
    // Инициализация структур данных
    Set set;
    set.count = 0;
    memset(set.elements, 0, sizeof(set.elements));
    Stack stack;
    stack.top = -1;
    memset(stack.elements, 0, sizeof(stack.elements));
    Queue queue;
    queue.back = 0;
    queue.front = 0;
    memset(queue.elements, 0, sizeof(queue.elements));
    HashTable hashTable;
    hashTable.count = 0;
    memset(hashTable.keys, 0, sizeof(hashTable.keys));
    memset(hashTable.values, 0, sizeof(hashTable.values));
    // Обработка запроса
    if (strcmp(query, "SADD") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable, client_socket);
        SADD(&set, argv[5], client_socket);
        send(client_socket, "Done!\n", sizeof("Done!\n"), 0);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "SREM") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable, client_socket);
        SREM(&set, argv[5], client_socket);
        send(client_socket, "Done!\n", sizeof("Done!\n"), 0);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "SISMEMBER") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable, client_socket);
        if (SISMEMBER(&set, argv[5]) == 1) {
            printf("TRUE\n");
            send(client_socket, "TRUE\n", sizeof("TRUE\n"), 0);
        }
        else {
            printf("FALSE\n");
            send(client_socket, "FALSE\n", sizeof("FALSE\n"), 0);
        }
    }
    else if (strcmp(query, "SPUSH") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable, client_socket);
        SPUSH(&stack, argv[5], client_socket);
        send(client_socket, "Done!\n", sizeof("Done!\n"), 0);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "SPOP") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable, client_socket);
        char* popped_item = SPOP(&stack);
        printf("Popped item: %s\n", popped_item);
        char message[32];
        sprintf(message, "Popped item: %s\n", popped_item);
        send(client_socket, message, strlen(message), 0);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "QPUSH") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable, client_socket);
        QPUSH(&queue, argv[5], client_socket);
        send(client_socket, "Done!\n", sizeof("Done!\n"), 0);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "QPOP") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable, client_socket);
        char* popped_item = QPOP(&queue);
        printf("Popped item: %s\n", popped_item);
        char message[32];
        sprintf(message, "Popped item: %s\n", popped_item);
        send(client_socket, message, strlen(message), 0);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "HSET") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable, client_socket);
        HSET(&hashTable, argv[5], argv[6], client_socket);
        send(client_socket, "Done!\n", sizeof("Done!\n"), 0);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else  if (strcmp(query, "HDEL") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable, client_socket);
        char* deleted_item = HDEL(&hashTable, argv[5]);
        printf("Deleted item: %s\n", deleted_item);
        char message[32];
        sprintf(message, "Deleted item: %s\n", deleted_item);
        send(client_socket, message, strlen(message), 0);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else  if (strcmp(query, "HGET") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable, client_socket);
        char* value = HGET(&hashTable, argv[5]);
        printf("Value: %s\n", value);
        char message[32];
        sprintf(message, "Value: %s\n", value);
        send(client_socket, message, strlen(message), 0);
    }
    // Закрытие файла и освобождение мьютекса
    fclose(file);
    ReleaseMutex(dbMutex);
    CloseHandle(dbMutex);
    // Освобождение памяти от аргументов командной строки
    for (int i = 0; i < 7; i++) {
        free(argv[i]);
    }
}

DWORD WINAPI threadFunction(LPVOID lpParam) {
    // Передача аргументов потока
    ThreadArgs* args = (ThreadArgs*)lpParam;

    // Получение сокетов
    SOCKET* s = args->serverSocket;
    SOCKET* client_socket = args->clientSocket;

    // Буфер для приема данных от клиента
    char buffer[20];
    char* argv[7];
    int argc = 7;
    memset(argv, 0, sizeof(argv));


    // Основной цикл обработки запросов от клиента
    while (1) {
        // Прием сообщения от клиента
        char working_buffer[40];
        memset(working_buffer, 0, sizeof(working_buffer));
        recv(client_socket, working_buffer, sizeof(working_buffer), 0);

        // Обработка сообщения от клиента
        if (strcmp(working_buffer, "Client disconnected!\n") == 0) {
            printf("%s", working_buffer);
        }
        else if (strcmp(working_buffer, "Client keep working!\n") == 0) {
            // Прием аргументов запроса от клиента
            for (int i = 0; i < 7; i++) {
                recv(client_socket, buffer, sizeof(buffer), 0);
                argv[i] = _strdup(buffer);
            }
            // Отправка подтверждения клиенту
            char ready_buffer[10] = "Done!\n";
            send(client_socket, ready_buffer, sizeof(ready_buffer), 0);
            // Вывод аргументов запроса на экран
            printf("Client answer: ");
            for (int i = 0; i < 7; i++) {
                printf("%s ", argv[i]);
            }
            printf("\n");
            // Вызов функции обработки запроса
            queryProcessing(argc, argv, client_socket);
        }
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "Rus");
    // Инициализация библиотеки Winsock
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);

    // Создание серверного сокета
    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);

    // Инициализация структуры сервера
    SOCKADDR_IN server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(6379);

    char c;
    printf("--------Welcome--------\n");
    printf("s - server\nk-client\n");
    printf("-----------------------\n");
    scanf_s("%c", &c);

    // Клиентский режим
    if (c == 'k') {
        server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
        if (connect(s, &server, sizeof(server)) == -1) {
            printf("Connection error!\n");
            Sleep(3000);
            return;
        }
        while (1) {
            printf("Would you like to disconnect?\n 1 - yes\n 2 - no\n");
            int disabling = 0;
            scanf_s("%d", &disabling);
            if (disabling == 1) {
                printf("Disconnecting!\n");
                char working_buffer[40]= "Client disconnected!\n";
                send(s, working_buffer, sizeof(working_buffer), 0);
                Sleep(3000);
                return;
            }
            else if (disabling == 2){
                char working_buffer[40] = "Client keep working!\n";
                send(s, working_buffer, sizeof(working_buffer), 0);
                printf("Enter a request:\n");
                char buffer[20];
                memset(buffer, 0, sizeof(buffer));
                for (int i = 0; i < 7; i++) {
                    scanf_s("%s", &buffer, 20);
                    send(s, buffer, sizeof(buffer), 0);
                }
                char ready_buffer[10];
                memset(ready_buffer, 0, sizeof(ready_buffer));
                recv(s, ready_buffer, sizeof(ready_buffer), 0);
                printf(ready_buffer);

                Sleep(1000);
                char answer_buffer[32];
                memset(answer_buffer, 0, sizeof(answer_buffer));

                // Принимаем данные от сервера
                int bytesReceived = recv(s, answer_buffer, sizeof(answer_buffer), 0);
                if (bytesReceived > 0) {
                    answer_buffer[bytesReceived] = '\n';
                    printf("Server answer: %s\n", answer_buffer);

                }

                Sleep(3000);
            }
        }

    }
    // Серверный режим
    if (c == 's') {
        bind(s, &server, sizeof(server));
        listen(s, 100);

        printf("Waiting for connection...\n");
        while (1) {
            ThreadArgs args;
            SOCKET client_socket;
            SOCKADDR_IN client_addr;
            int client_addr_size = sizeof(client_addr);
            if (client_socket = accept(s, &client_addr, &client_addr_size)) {
                printf("connect OK\n");
                args.clientSocket = client_socket;
                args.serverSocket = s;
                HANDLE thread = CreateThread(NULL, 0, threadFunction, (LPVOID)&args, NULL, 0, NULL);
                if (thread == NULL) {
                    printf("Thread creation failed\n");
                    continue;
                }
            }
            else {
                printf("connect NOT OK\n");
                return;
            }
        }
    }
    // Закрытие сокета и освобождение ресурсов Winsock
    closesocket(s);
    WSACleanup();
}

// Множество
void SADD(Set* set, char* value, SOCKET* client_socket) {
    if (set->count < SIZE) {
        int index = hash(value);
        if (set->elements[index] == NULL) {
            set->elements[index] = _strdup(value);
            set->count++;
        }
        else {
            printf("This cell is already employed.\n");
            send(client_socket, "This cell is already employed.\n", sizeof("This cell is already employed.\n"), 0);
        }
    }
    else {
        printf("Set is full.\n");
        send(client_socket, "Set is full.\n", sizeof("Set is full.\n"), 0);
    }
}

void SREM(Set* set, char* value, SOCKET* client_socket) {
    int index = hash(value);
    if (set->elements[index] != NULL) {
        free(set->elements[index]);
        set->elements[index] = NULL;
        set->count--;
    }
    else {
        printf("There is no such element.\n");
        send(client_socket, "There is no such element.\n", sizeof("There is no such element.\n"), 0);
    }
}

int SISMEMBER(Set* set, char* value) {
    int index = hash(value);
    if (set->elements[index] != NULL) {
        return 1;
    }
    else {
        return -1;
    }
}

// Стек
void SPUSH(Stack* stack, char* value, SOCKET* client_socket) {
    if (stack->top < SIZE - 1) {
        stack->top++;
        stack->elements[stack->top] = _strdup(value);
    }
    else {
        printf("Stack is full.\n");
        send(client_socket, "Stack is full.\n", sizeof("Stack is full.\n"), 0);
    }
}

char* SPOP(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack is empty.\n");
        return NULL;
    }
    char* value = stack->elements[stack->top];
    stack->elements[stack->top] = NULL;
    stack->top--;
    return value;
}

// Очередь
void QPUSH(Queue* queue, char* value, SOCKET* client_socket) {
    if (queue->back < SIZE - 1) {
        queue->elements[queue->back] = _strdup(value);
        queue->back++;
    }
    else {
        printf("Queue is full.\n");
        send(client_socket, "Queue is full.\n", sizeof("Queue is full.\n"), 0);
    }
}

char* QPOP(Queue* queue) {
    if (queue->front == queue->back) {
        printf("Queue is empty.\n");
        return NULL;
    }
    char* value = queue->elements[queue->front];
    queue->elements[queue->front] = NULL;
    queue->front++;
    return value;
}

// Хэш-таблица (теперь есть обработка коллизий через двойной хэш)
void HSET(HashTable* hashtable, char* key, char* value, SOCKET* client_socket) {
    if (hashtable->count < SIZE) {
        int index = hash(key);
        int step = secondHash(key);
        if (hashtable->keys[index] == NULL) {
            hashtable->keys[index] = _strdup(key);
            hashtable->values[index] = _strdup(value);
        }
        else if (strcmp(hashtable->keys[index], key) != 0) {
            while (hashtable->keys[index] != NULL) {
                index = (index + step) % SIZE;
            }
            hashtable->keys[index] = _strdup(key);
            hashtable->values[index] = _strdup(value);
        }
        else {
            printf("Key already exists.\n");
            send(client_socket, "Key already exists.\n", sizeof("Key already exists.\n"), 0);

        }
    }
    else {
        printf("HashTable is full.\n");
        send(client_socket, "HashTable is full.\n", sizeof("HashTable is full.\n"), 0);
    }
}

char* HDEL(HashTable* hashtable, char* key) {
    int index = hash(key);
    if (hashtable->keys[index] == NULL || hashtable->values[index] == NULL) {
        printf("This cell is already empty.\n");
    }
    else {
        char* value = hashtable->values[index];
        hashtable->keys[index] = NULL;
        hashtable->values[index] = NULL;
        hashtable->count--;
        return value;
    }
}

char* HGET(HashTable* hashtable, char* key) {
    int index = hash(key);
    if (hashtable->keys[index] != NULL && hashtable->values[index] != NULL) {
        return hashtable->values[index];
    }
    else {
        printf("There is no such element.\n");
        return NULL;
    }

}


