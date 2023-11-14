#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define SIZE 901

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
void SADD(Set* set, char* value);
void SREM(Set* set, char* value);
int SISMEMBER(Set* set, char* value);

// Стек
void SPUSH(Stack* stack, char* value);
char* SPOP(Stack* stack);

// Очередь
void QPUSH(Queue* queue, char* value);
char* QPOP(Queue* queue);

// Хэш-таблица
void HSET(HashTable* hashtable, char* key, char* value);
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

void copyingValuesFromFile(FILE* file, Set* set, Stack* stack, Queue* queue, HashTable* hashTable) {
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
        SADD(set, line);
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
        SPUSH(stack, stackData[i]);
    }
    fseek(file, queue_current_pos, SEEK_SET);
    while (fgets(line, sizeof(line), file) != NULL && ftell(file) < hashtable_current_pos) {
        removeNewline(line);
        QPUSH(queue, line);
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
            HSET(hashTable, key, value);
            free(key);
            key = NULL;
            free(value);
            value = NULL;
        }
    }
    fclose(file);
}
//---------------------------------------------
            // cd C:\Users\Никита Сильченко\source\repos\Prakt_1\x64\Debug
            // Prakt_1 --file C:\data.txt --query SADD item
            // Prakt_1 --file C:\data.txt --query SREM item
            // Prakt_1 --file C:\data.txt --query SISMEMBER item
            // 
            // Prakt_1 --file C:\data.txt --query SPUSH item
            // Prakt_1 --file C:\data.txt --query SPOP
            // 
            // Prakt_1 --file C:\data.txt --query QPUSH item1
            // Prakt_1 --file C:\data.txt --query QPOP
            // 
            // Prakt_1 --file C:\data.txt --query HSET key1 value1
            // Prakt_1 --file C:\data.txt --query HDEL key1
            // Prakt_1 --file C:\data.txt --query HGET key1
// Мэйн
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");
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
    if (strcmp(query, "SADD") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable);
        SADD(&set, argv[5]);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "SREM") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable);
        SREM(&set, argv[5]);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "SISMEMBER") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable);
        if (SISMEMBER(&set, argv[5]) == 1) {
            printf("TRUE\n");
        }
        else {
            printf("FALSE\n");
        }
    }
    else if (strcmp(query, "SPUSH") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable);
        SPUSH(&stack, argv[5]);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "SPOP") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable);
        char* popped_item = SPOP(&stack);
        printf("Popped item: %s\n", popped_item);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "QPUSH") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable);
        QPUSH(&queue, argv[5]);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "QPOP") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable);
        char* popped_item = QPOP(&queue);
        printf("Popped item: %s\n", popped_item);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else if (strcmp(query, "HSET") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable);
        HSET(&hashTable, argv[5], argv[6]);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else  if (strcmp(query, "HDEL") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable);
        char* deleted_item = HDEL(&hashTable, argv[5]);
        printf("Deleted item: %s\n", deleted_item);
        fileUpdate(file, filename, &set, &stack, &queue, &hashTable);
    }
    else  if (strcmp(query, "HGET") == 0) {
        copyingValuesFromFile(file, &set, &stack, &queue, &hashTable);
        char* value = HGET(&hashTable, argv[5]);
        printf("Value: %s\n", value);
    }
    fclose(file);
}

// Множество
void SADD(Set* set, char* value) {
    if (set->count < SIZE) {
        int index = hash(value);
        if (set->elements[index] == NULL) {
            set->elements[index] = _strdup(value);
            set->count++;
        }
        else {
            printf("This cell is already employed.\n");
        }
    }
    else {
        printf("Set is full.\n");
    }
}

void SREM(Set* set, char* value) {
    int index = hash(value);
    if (set->elements[index] != NULL) {
        free(set->elements[index]);
        set->elements[index] = NULL;
        set->count--;
    }
    else {
        printf("There is no such element.\n");
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
void SPUSH(Stack* stack, char* value) {
    if (stack->top < SIZE - 1) {
        stack->top++;
        stack->elements[stack->top] = _strdup(value);
    }
    else {
        printf("Stack is full.\n");
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
void QPUSH(Queue* queue, char* value) {
    if (queue->back < SIZE - 1) {
        queue->elements[queue->back] = _strdup(value);
        queue->back++;
    }
    else {
        printf("Queue is full.\n");
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


