#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include <winsock2.h>

#define SIZE 1901

HANDLE dbMutex;

typedef struct {
    char* keys[SIZE];
    char* values[SIZE];
    int count;
} HashTable;

unsigned int hash(const char* key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = hash * 31 + key[i];
    }
    return hash % SIZE;
}


int secondHash(char* str) {
    return 7 - (hash(str) % 7);
}

// Хэш-таблица
void HSET(HashTable* hashtable, char* key, char* value);

void fileUpdate(FILE* file, char* filename, HashTable* hashTable) {
    fopen_s(&file, filename, "w");
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


void copyingValuesFromFile(FILE* file, HashTable* hashTable) {
    char line[256];
    long hashtable_current_pos = -1;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "HASHTABLE:\n") == 0) {
            hashtable_current_pos = ftell(file);
        }
    }
    rewind(file);
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
            HSET(hashTable, key, value);
            free(key);
            key = NULL;
            free(value);
            value = NULL;
        }
    }
    fclose(file);
}

void queryProcessing(SOCKET client_socket) {
    char* argv[7];
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("connect OK\n");
    printf("Client answer: %s\n", buffer);
    int argc = 0;
    char* token = strtok(buffer, " ");  // Разделяем строку по пробелу
    while (token != NULL && argc < 7) {
        argv[argc] = _strdup(token);
        argc++;
        token = strtok(NULL, " ");
    }
    dbMutex = CreateMutex(NULL, FALSE, NULL);
    if (dbMutex == NULL) {
        printf("Mutex creation error.\n");
        return -1;
    }
    WaitForSingleObject(dbMutex, INFINITE);
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

    HashTable hashTable;
    hashTable.count = 0;
    memset(hashTable.keys, 0, sizeof(hashTable.keys));
    memset(hashTable.values, 0, sizeof(hashTable.values));
    if (strcmp(query, "HSET") == 0) {
        copyingValuesFromFile(file, &hashTable);
        HSET(&hashTable, argv[5], argv[6]);
        fileUpdate(file, filename, &hashTable);
    }

    fclose(file);
    ReleaseMutex(dbMutex);
    CloseHandle(dbMutex);
    for (int i = 0; i < 7; i++) {
        free(argv[i]);
    }
}

DWORD WINAPI threadFunction(LPVOID lpParam) {
    SOCKET client_socket = (SOCKET)lpParam;
    queryProcessing(client_socket);
    return 0;
}

int main() {
    setlocale(LC_ALL, "Rus");
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);

    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(6379);

    char c;
    printf("--------Welcome--------\n");
    printf("s - server\nk-client\n");
    printf("-----------------------\n");
    scanf_s("%c", &c);

    if (c == 'k') {
        server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
        connect(s, &server, sizeof(server));

        printf("Enter a request:\n");
        char buffer[20];
        for (int i = 0; i < 7; i++) {
            scanf_s("%s", buffer, 20);
            send(s, buffer, sizeof(buffer), 0);
        }

        char ready_buffer[10];
        memset(ready_buffer, 0, sizeof(ready_buffer));
        recv(s, ready_buffer, sizeof(ready_buffer), 0);
        printf(ready_buffer);

        Sleep(3000);
    }
    if (c == 's') {
        bind(s, &server, sizeof(server));
        listen(s, 100);

        char buffer[20];
        char* argv[7];
        memset(argv, 0, sizeof(argv));

        SOCKET client_socket;
        SOCKADDR_IN client_addr;
        int client_addr_size = sizeof(client_addr);
        printf("Waiting for connection...\n");
        while (client_socket = accept(s, &client_addr, &client_addr_size)) {
            HANDLE thread = CreateThread(NULL, 0, threadFunction, (LPVOID)client_socket, NULL, 0, NULL);
            if (thread == NULL) {
                printf("Thread creation failed\n");
                return -1;
            }
            CloseHandle(thread);
        }
    }

    closesocket(s);
    WSACleanup();
}

// Хэш-таблица (теперь есть обработка коллизий через двойной хэш)
void HSET(HashTable* hashtable, char* key, char* value) {
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
        }
    }
    else {
        printf("HashTable is full.\n");
    }
}



