#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define SIZE 901

// Массив
//---------------------------
typedef struct {
    char* elements[SIZE];
    int count;
} Array;
//---------------------------

// Односвязный
//---------------------------
typedef struct {
    char* data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} SinglyLinkedList;
//---------------------------

// Двусвязный
//---------------------------
typedef struct {
    char* data;
    struct DoubleNode* next;
    struct DoubleNode* prev;
} DoubleNode;

typedef struct {
    DoubleNode* head;
    DoubleNode* tail;
} DoublyLinkedList;
//---------------------------

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


// Бинарное дерево поиска
//---------------------------
typedef struct {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
//---------------------------

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

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode) {
        newNode->data = data;
        newNode->left = newNode->right = NULL;
    }
    return newNode;
}

void rootsToFile(TreeNode* root, FILE* file) {
    if (root != NULL) {
        rootsToFile(root->left, file);
        fprintf(file, "%d\n", root->data);
        rootsToFile(root->right, file);
    }
}

// Массив
void AADD(Array* array, char* value);
void AREM(Array* array, int index);
int AISMEMBER(Array* array, int index);

// Односвязный список
void SLLADD(SinglyLinkedList* singlyLinkedList, char* value);
char* SLLPOP(SinglyLinkedList* singlyLinkedList);
void SLLREM(SinglyLinkedList* singlyLinkedList, char* value);
int SLLISMEMBER(SinglyLinkedList* singlyLinkedList, char* value);
void SLLPR(SinglyLinkedList* singlyLinkedList);

// Двусвязный список
void DLLADD(DoublyLinkedList* doublyLinkedList, char* value);
char* DLLPOP(DoublyLinkedList* doublyLinkedList);
void DLLREM(DoublyLinkedList* doublyLinkedList, char* value);
int DLLISMEMBER(DoublyLinkedList* doublyLinkedList, char* value);
void DLLADDTOEND(DoublyLinkedList* doublyLinkedList, char* value);
char* DLLPOPEND(DoublyLinkedList* doublyLinkedList);
void DLLPR(DoublyLinkedList* doublyLinkedList);

// Стек
void SPUSH(Stack* stack, char* value);
char* SPOP(Stack* stack);

// Очередь
void QPUSH(Queue* queue, char* value);
char* QPOP(Queue* queue);

// Хэш-таблица
void HSET(HashTable* hashtable, char* key, char* value);
void HDEL(HashTable* hashtable, char* key);
char* HGET(HashTable* hashtable, char* key);
void TPRINT(TreeNode* root);

// Бинарное дерево поиска
TreeNode* TADD(TreeNode* root, int value);
TreeNode* TDEL(TreeNode* root, int value);
TreeNode* TISMEMBER(TreeNode* root, int value);


void fileUpdate(FILE* file, char* filename, Array* array, SinglyLinkedList* singlyLinkedList, DoublyLinkedList* doublyLinkedList, Stack* stack, Queue* queue, HashTable* hashTable, TreeNode* root) {
    fopen_s(&file, filename, "w");
    fputs("ARRAY:\n", file);
    for (int i = 0; i < array->count; i++) {
        if (array->elements[i] != NULL) {
            fputs(array->elements[i], file);
            fputs("\n", file);
        }
    }
    fputs("SINGLY LINKED LIST:\n", file);
    Node* current = singlyLinkedList->head;
    while (current != NULL) {
        fputs(current->data, file);
        fputs("\n", file);
        current = current->next;
    }
    fputs("DOUBLY LINKED LIST:\n", file);
    DoubleNode* double_current = doublyLinkedList->head;
    while (double_current != NULL) {
        fputs(double_current->data, file);
        fputs("\n", file);
        double_current = double_current->next;
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
    fputs("BINARY SEARCH TREE:\n", file);
    if (root != NULL) {
        rootsToFile(root, file);
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

void copyingValuesFromFile(FILE* file, Array* array, SinglyLinkedList* singlyLinkedList, DoublyLinkedList* doublyLinkedList, Stack* stack, Queue* queue, HashTable* hashTable) {
    char line[128];
    long arr_current_pos = -1, stack_current_pos = -1, queue_current_pos = -1, hashtable_current_pos = -1, singly_linked_list_pos = -1, doubly_linked_list_pos = -1, binary_search_tree_pos = -1;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "ARRAY:\n") == 0) {
            arr_current_pos = ftell(file);
        }
        else if (strcmp(line, "SINGLY LINKED LIST:\n") == 0) {
            singly_linked_list_pos = ftell(file);
        }
        else if (strcmp(line, "DOUBLY LINKED LIST:\n") == 0) {
            doubly_linked_list_pos = ftell(file);
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
        else if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
            binary_search_tree_pos = ftell(file);
        }
        
    }
    rewind(file);
    //-------------------------------------------
    fseek(file, arr_current_pos, SEEK_SET);
    while (fgets(line, sizeof(line), file) != NULL && ftell(file) < singly_linked_list_pos) {
        removeNewline(line);
        AADD(array, line);
    }
    //-------------------------------------------
    fseek(file, singly_linked_list_pos, SEEK_SET);
    char singleListData[SIZE][128];
    int singleListDataIndex = 0;
    while (fgets(line, sizeof(line), file) != NULL && ftell(file) < doubly_linked_list_pos) {
        removeNewline(line);
        strcpy_s(singleListData[singleListDataIndex], sizeof(singleListData[singleListDataIndex]), line);
        singleListDataIndex++;
    }
    for (int i = singleListDataIndex - 1; i >= 0; i--) {
        SLLADD(singlyLinkedList, singleListData[i]);
    }
    //------------------------------------------
    fseek(file, doubly_linked_list_pos, SEEK_SET);
    char doublyListData[SIZE][128];
    int doublyListDataIndex = 0;
    while (fgets(line, sizeof(line), file) != NULL && ftell(file) < stack_current_pos) {
        removeNewline(line);
        strcpy_s(doublyListData[doublyListDataIndex], sizeof(doublyListData[doublyListDataIndex]), line);
        doublyListDataIndex++;
    }
    for (int i = doublyListDataIndex - 1; i >= 0; i--) {
        DLLADD(doublyLinkedList, doublyListData[i]);
    }
    //------------------------------------------
    fseek(file, stack_current_pos, SEEK_SET);
    char stackData[SIZE][128];
    int stackDataIndex = 0;
    while (fgets(line, sizeof(line), file) != NULL && ftell(file) < queue_current_pos) {
        removeNewline(line);
        strcpy_s(stackData[stackDataIndex], sizeof(stackData[stackDataIndex]), line);
        stackDataIndex++;
    }
    for (int i = stackDataIndex - 1; i >= 0; i--) {
        SPUSH(stack, stackData[i]);
    }
    //-------------------------------------------
    fseek(file, queue_current_pos, SEEK_SET);
    while (fgets(line, sizeof(line), file) != NULL && ftell(file) < hashtable_current_pos) {
        removeNewline(line);
        QPUSH(queue, line);
    }
    //-------------------------------------------
    fseek(file, hashtable_current_pos, SEEK_SET);
    char* key = NULL;
    while (fgets(line, sizeof(line), file) != NULL && ftell(file) < binary_search_tree_pos) {
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
}
//---------------------------------------------
            // cd C:\Users\Никита Сильченко\source\repos\Lab_1\x64\Debug
            // Lab_1 --file C:\newdata.txt --query AADD item            +
            // Lab_1 --file C:\newdata.txt --query AREM 5
            // Lab_1 --file C:\newdata.txt --query AISMEMBER 5
            // 
            // Lab_1 --file C:\newdata.txt --query SLLADD item          +
            // Lab_1 --file C:\newdata.txt --query SLLPOP               +
            // Lab_1 --file C:\newdata.txt --query SLLREM item
            // Lab_1 --file C:\newdata.txt --query SLLISMEMBER item
            // Lab_1 --file C:\newdata.txt --query SLLPR
            // 
            // Lab_1 --file C:\newdata.txt --query DLLADD item          +
            // Lab_1 --file C:\newdata.txt --query DLLPOP               +
            // Lab_1 --file C:\newdata.txt --query DLLREM item          
            // Lab_1 --file C:\newdata.txt --query DLLISMEMBER item     
            // Lab_1 --file C:\newdata.txt --query DLLADDTOEND item   
            // Lab_1 --file C:\newdata.txt --query DLLPOPEND  
            // Lab_1 --file C:\newdata.txt --query DLLPR            
            // 
            // Lab_1 --file C:\newdata.txt --query SPUSH item           +
            // Lab_1 --file C:\newdata.txt --query SPOP                 +
            // 
            // Lab_1 --file C:\newdata.txt --query QPUSH item           +
            // Lab_1 --file C:\newdata.txt --query QPOP                 +
            // 
            // Lab_1 --file C:\newdata.txt --query HSET key1 value1
            // Lab_1 --file C:\newdata.txt --query HDEL key1            +
            // Lab_1 --file C:\newdata.txt --query HGET key1            +
            // 
            // Lab_1 --file C:\newdata.txt --query TADD 50              +
            // Lab_1 --file C:\newdata.txt --query TDEL 50              +
            // Lab_1 --file C:\newdata.txt --query TISMEMBER 50         +
            // Lab_1 --file C:\newdata.txt --query TPRINT

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
    Array array;
    array.count = 0;
    memset(array.elements, 0, sizeof(array.elements));
    SinglyLinkedList singlyLinkedList;
    singlyLinkedList.head = NULL;
    DoublyLinkedList doublyLinkedList;
    doublyLinkedList.head = NULL;
    doublyLinkedList.tail = NULL;
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
    TreeNode* root = NULL;
    if (strcmp(query, "AADD") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        AADD(&array, argv[5]);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "AREM") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        int index = atoi(argv[5]);
        AREM(&array, index);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "AISMEMBER") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        int index = atoi(argv[5]);
        if (AISMEMBER(&array, index) == 1) {
            printf("TRUE\n");
        }
        else {
            printf("FALSE\n");
        }
    }
    else if (strcmp(query, "SLLADD") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        SLLADD(&singlyLinkedList, argv[5]);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "SLLPOP") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        char* popped_item = SLLPOP(&singlyLinkedList);
        printf("Popped item: %s\n", popped_item);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "SLLREM") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        SLLREM(&singlyLinkedList, argv[5]);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "SLLISMEMBER") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        if (SLLISMEMBER(&singlyLinkedList, argv[5]) == 1) {
            printf("TRUE\n");
        }
        else {
            printf("FALSE\n");
        }
    }
    else if (strcmp(query, "SLLPR") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        SLLPR(&singlyLinkedList);
    }
    else if (strcmp(query, "DLLADD") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        DLLADD(&doublyLinkedList, argv[5]);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "DLLPOP") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        char* popped_item = DLLPOP(&doublyLinkedList);
        printf("Popped item: %s\n", popped_item);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "DLLREM") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        DLLREM(&doublyLinkedList, argv[5]);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "DLLISMEMBER") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        if (DLLISMEMBER(&doublyLinkedList, argv[5]) == 1) {
            printf("TRUE\n");
        }
        else {
            printf("FALSE\n");
        }
    }
    else if (strcmp(query, "DLLADDTOEND") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        DLLADDTOEND(&doublyLinkedList, argv[5]);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "DLLPOPEND") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        char* popped_item = DLLPOPEND(&doublyLinkedList);
        printf("Popped item: %s\n", popped_item);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "DLLPR") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        DLLPR(&doublyLinkedList);
    }
    else if (strcmp(query, "SPUSH") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        SPUSH(&stack, argv[5]);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "SPOP") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        char* popped_item = SPOP(&stack);
        printf("Popped item: %s\n", popped_item);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "QPUSH") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        QPUSH(&queue, argv[5]);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "QPOP") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        char* popped_item = QPOP(&queue);
        printf("Popped item: %s\n", popped_item);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "HSET") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        HSET(&hashTable, argv[5], argv[6]);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else  if (strcmp(query, "HDEL") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        HDEL(&hashTable, argv[5]);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else  if (strcmp(query, "HGET") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        char* value = HGET(&hashTable, argv[5]);
        printf("Value: %s\n", value);
    }
    else if (strcmp(query, "TADD") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        int value = atoi(argv[5]);
        root = TADD(root, value);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "TDEL") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        int value = atoi(argv[5]);
        root = TDEL(root, value);
        fileUpdate(file, filename, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable, root);
    }
    else if (strcmp(query, "TISMEMBER") == 0) {
        copyingValuesFromFile(file, &array, &singlyLinkedList, &doublyLinkedList, &stack, &queue, &hashTable);
        char line[128];
        long binary_search_tree_pos = -1;
        rewind(file);
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strcmp(line, "BINARY SEARCH TREE:\n") == 0) {
                binary_search_tree_pos = ftell(file);
            }
        }
        rewind(file);

        fseek(file, binary_search_tree_pos, SEEK_SET);
        while (fgets(line, sizeof(line), file) != NULL) {
            removeNewline(line);
            removeNewline(line);
            int current_value = atoi(line);
            root = TADD(root, current_value);
        }
        fclose(file);
        int value = atoi(argv[5]);
        TreeNode* result = TISMEMBER(root, value);
        if (result != NULL) {
            printf("TRUE\n");
        }
        else {
            printf("FALSE\n");
        }
    }
    else if (strcmp(query, "TPRINT") == 0) {
        root = TADD(root, 8);
        root = TADD(root, 10);
        root = TADD(root, 3);
        root = TADD(root, 14);
        root = TADD(root, 6);
        root = TADD(root, 1);
        root = TADD(root, 4);
        root = TADD(root, 7);
        root = TADD(root, 13);
        root = TADD(root, 2);
        TPRINT(root, 0);
    }
    fclose(file);
}

// Массив (теперь удаление по индексу + смещение элементов на удалённые места и чтение элемента по индексу)
void AADD(Array* array, char* value) {
    if (array->count < SIZE) {
        array->elements[array->count] = _strdup(value);
        array->count++;
    }
    else {
        printf("Array is full.\n");
    }
}

void AREM(Array* array, int index) {
    if (index < 0 || index >= array->count) {
        return;
    }
    free(array->elements[index]);
    for (int i = index; i < array->count - 1; i++) {
        array->elements[i] = array->elements[i + 1];
    }
    array->count--;
}

int AISMEMBER(Array* array, int index) {
    if (index < 0 || index >= array->count) {
        return 0;
    }
    return 1;
}

// Односвязный список
void SLLADD(SinglyLinkedList* singlyLinkedList, char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = _strdup(value);
    newNode->next = singlyLinkedList->head;
    singlyLinkedList->head = newNode;
}

char* SLLPOP(SinglyLinkedList* singlyLinkedList) {
    if (singlyLinkedList->head != NULL) {
        Node* temp = singlyLinkedList->head;
        singlyLinkedList->head = singlyLinkedList->head->next;
        char* deletedValue;
        deletedValue = temp->data;
        free(temp);
        return deletedValue;
    }
    else {
        return NULL;
    }
}

// Удаление по значению
void SLLREM(SinglyLinkedList* singlyLinkedList, char* value) {
    if (singlyLinkedList == NULL || singlyLinkedList->head == NULL) {
        return;
    }
    Node* current = singlyLinkedList->head;
    Node* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->data, value) == 0) {
            if (previous == NULL) {
                singlyLinkedList->head = current->next;
            }
            else {
                previous->next = current->next;
            }
            free(current->data);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Поиск по значению
int SLLISMEMBER(SinglyLinkedList* singlyLinkedList, char* value) {
    if (singlyLinkedList == NULL || singlyLinkedList->head == NULL) {
        return -1;
    }
    Node* current = singlyLinkedList->head;
    while (current != NULL) {
        if (strcmp(current->data, value) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Визуализация по порядку
void SLLPR(SinglyLinkedList* singlyLinkedList) {
    if (singlyLinkedList == NULL || singlyLinkedList->head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* current = singlyLinkedList->head;
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Двусвязный список
void DLLADD(DoublyLinkedList* doublyLinkedList, char* value) {
    DoubleNode* newNode = (DoubleNode*)malloc(sizeof(DoubleNode));
    newNode->data = _strdup(value);
    newNode->next = doublyLinkedList->head;
    newNode->prev = NULL;
    if (doublyLinkedList->head == NULL) {
        doublyLinkedList->tail = newNode;
    }
    else {
        doublyLinkedList->head->prev = newNode;
    }
    doublyLinkedList->head = newNode;
}

char* DLLPOP(DoublyLinkedList* doublyLinkedList) {
    if (doublyLinkedList->head != NULL) {
        DoubleNode* temp = doublyLinkedList->head;
        doublyLinkedList->head = doublyLinkedList->head->next;
        if (doublyLinkedList->head == NULL) {
            doublyLinkedList->tail = NULL;
        }
        else {
            doublyLinkedList->head->prev = NULL;
        }
        char* deletedValue;
        deletedValue = temp->data;
        free(temp);
        return deletedValue;
    }
    else {
        return NULL;
    }
}

// Удаление по значению
void DLLREM(DoublyLinkedList* doublyLinkedList, char* value) {
    if (doublyLinkedList == NULL || doublyLinkedList->head == NULL) {
        return;
    }
    DoubleNode* current = doublyLinkedList->head;
    DoubleNode* next = current->next;
    DoubleNode* previous = current->prev;
    while (current != NULL) {
        if (strcmp(current->data, value) == 0) {
            if (current == doublyLinkedList->head) {
                doublyLinkedList->head = current->next;
                if (doublyLinkedList->head != NULL) {
                    doublyLinkedList->head->prev = NULL;
                }
            }
            else {
                previous->next = next;
                if (current == doublyLinkedList->tail) {
                    doublyLinkedList->tail = current->prev;
                }
                else {
                    next->prev = previous;
                }
            }
            free(current->data);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
        next = current->next;
    }
}

// Поиск по значению
int DLLISMEMBER(DoublyLinkedList* doublyLinkedList, char* value) {
    if (doublyLinkedList == NULL || doublyLinkedList->head == NULL) {
        return -1;
    }
    Node* current = doublyLinkedList->head;
    while (current != NULL) {
        if (strcmp(current->data, value) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Добавление в конец
void DLLADDTOEND(DoublyLinkedList* doublyLinkedList, char* value) {
    DoubleNode* newNode = (DoubleNode*)malloc(sizeof(DoubleNode));
    newNode->data = _strdup(value);
    newNode->next = NULL;
    newNode->prev = doublyLinkedList->tail;
    if (doublyLinkedList->tail == NULL) {
        doublyLinkedList->head = newNode;
    }
    else {
        doublyLinkedList->tail->next = newNode;
    }
    doublyLinkedList->tail = newNode;
}

char* DLLPOPEND(DoublyLinkedList* doublyLinkedList) {
    if (doublyLinkedList->tail != NULL) {
        DoubleNode* temp = doublyLinkedList->tail;
        doublyLinkedList->tail = doublyLinkedList->tail->prev;
        if (doublyLinkedList->tail == NULL) {
            doublyLinkedList->head = NULL;
        }
        else {
            doublyLinkedList->tail->next = NULL;
        }
        char* deletedValue;
        deletedValue = temp->data;
        free(temp);
        return deletedValue;
    }
    else {
        return NULL;
    }
}

// Визуализация по порядку
void DLLPR(DoublyLinkedList* doublyLinkedList) {
    if (doublyLinkedList == NULL || doublyLinkedList->head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* current = doublyLinkedList->head;
    printf("NULL <-> ");
    while (current != NULL) {
        printf("%s <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
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

// Хэш-таблица
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

void HDEL(HashTable* hashtable, char* key) {
    int index = hash(key);
    if (hashtable->keys[index] == NULL && hashtable->keys[index] == NULL) {
        printf("This cell is already empty.\n");
    }
    else {
        free(hashtable->keys[index]);
        free(hashtable->values[index]);
        hashtable->keys[index] = NULL;
        hashtable->values[index] = NULL;
        hashtable->count--;
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

// Бинарное дерево поиска
TreeNode* TADD(TreeNode* root, int value) {
    if (root == NULL) {
        root = createNode(value);
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

TreeNode* TDEL(TreeNode* root, int value) {
    if (root == NULL) {
        return root;
    }
    if (value < root->data) {
        root->left = TDEL(root->left, value);
    }
    else if (value > root->data) {
        root->right = TDEL(root->right, value);
    }
    else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = root->right;
        while (temp != NULL && temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = TDEL(root->right, temp->data);
    }
    return root;
}

TreeNode* TISMEMBER(TreeNode* root, int value) {
    if (root == NULL || value == root->data) {
        return root;
    }
    if (value < root->data) {
        return TISMEMBER(root->left, value);
    }
    return TISMEMBER(root->right, value);
}

void TPRINT(TreeNode* root, int level) {
    if (root == NULL) {
        return;
    }
    TPRINT(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("\t");
    }
    printf("%d\n", root->data);
    TPRINT(root->left, level + 1);
}
