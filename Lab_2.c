#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <limits.h>

#define STACK_SIZE 100
#define SET_SIZE 10
#define ARRAY_SIZE 10
#define HASHTABLE_SIZE 128

typedef struct {
    char elements[STACK_SIZE];
    int top;
} Stack;

typedef struct {
    int elements[SET_SIZE];
    int count;
} Set;

typedef struct {
    int elements[ARRAY_SIZE];
    int count;
} Array;

typedef struct {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    char* keys[HASHTABLE_SIZE];
    char* values[HASHTABLE_SIZE];
} HashTable;

// Задание 1 ---------------------------------------------
/*последовательность "({})" - верная, последовательности "({)}" и "(][)"
- неверные. */
void SPUSH(Stack* stack, char symbol) {
    if (stack->top != STACK_SIZE - 1) {
        stack->top++;
        stack->elements[stack->top] = symbol;
    }
    else {
        printf("Стек переполнен.\n");
    }
}

int isBalanced(char* expression) {
    Stack stack;
    stack.top = -1;
    memset(stack.elements, 0, sizeof(stack.elements));
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[') {
            SPUSH(&stack, expression[i]);
        }
        else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']') {
            if (stack.top == -1) {
                return 0;
            }
            char top_char = stack.elements[stack.top];
            stack.top--;
            if ((expression[i] == ')' && top_char != '(') ||
                (expression[i] == '}' && top_char != '{') ||
                (expression[i] == ']' && top_char != '[')) {
                return 0;
            }
        }
    }
    if (stack.top == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

//--------------------------------------------------------
// Задание 2 ---------------------------------------------

int sumOfSet(Set* set) {
    int sum = 0;
    for (int i = 0; i < set->count; i++) {
        sum += set->elements[i];
    }
    return sum;
}

void SADD(Set* set, int value, int index) {
    if (set->count < SET_SIZE) {
        if (set->elements[index] == NULL) {
            set->elements[index] = value;
            set->count++;
        }
        else {
            printf("Этот индекс уже занят.\n");
        }
    }
    else {
        printf("Множество переполнено.\n");
    }
}

int isSubsetUnique(Set subsets[], int numSubsets, Set currentSet) {
    for (int i = 0; i < numSubsets; i++) {
        int isUnique = 1;
        for (int j = 0; j < currentSet.count; j++) {
            for (int k = 0; k < subsets[i].count; k++) {
                if (currentSet.elements[j] == subsets[i].elements[k]) {
                    isUnique = 0;
                    break;
                }
            }
            if (!isUnique) break;
        }
        if (!isUnique) return 0;
    }
    return 1;
}

/*Пример:
множество S = {4, 10, 5, 1, 3, 7}.
Необходимо в каждом подмножестве расположить элементы, сумма которых
равна 10.
Получим три подмножества {10}, {3, 7} и {4, 5, 1}.
Необходимо в каждом подмножестве расположить элементы, сумма которых
равна 15.
Получим два подмножества {4, 10, 1} и {5, 3, 7}.
 2 6 8 10 5 3
*/

void findUniqueSubsetsWithEqualSum(Set originalSet, Set currentSet, int index, int targetSum, Set subsets[], int* numSubsets) {
    if (currentSet.count > 0) {
        int sum = 0;
        for (int i = 0; i < currentSet.count; i++) {
            sum += currentSet.elements[i];
        }

        if (sum == targetSum && isSubsetUnique(subsets, *numSubsets, currentSet)) {
            subsets[*numSubsets] = currentSet;
            (*numSubsets)++;
            printf("Уникальное подмножество с равной суммой: ");
            for (int i = 0; i < currentSet.count; i++) {
                printf("%d ", currentSet.elements[i]);
            }
            printf("\n");
        }
    }

    for (int i = index; i < originalSet.count; i++) {
        currentSet.elements[currentSet.count] = originalSet.elements[i];
        currentSet.count++;
        findUniqueSubsetsWithEqualSum(originalSet, currentSet, i + 1, targetSum, subsets, numSubsets);
        currentSet.count--;
    }
}

//--------------------------------------------------------
// Задание 3 ---------------------------------------------

void AADD(Array* array, int value) {
    if (array->count < ARRAY_SIZE) {
        array->elements[array->count] = value;
        array->count++;
    }
    else {
        printf("Массив переполнен.\n");
    }
}

/*Пример:
Массив [ 4, -7, 1, 5, -4, 0, -3, 2, 4, 1]
Подмассив с наибольшей суммой - [2, 4, 1, 4]

Input:  {-3, 1, -3, 4, -1, 2, 1, -5, 4}
Output: Subarray with the largest sum is {4, -1, 2, 1} with sum 6.

Input:  {2, 1, -5, 4, -3, 1, -3, 4, -1}
Output: Subarray with the largest sum is {4, -1, 2, 1} with sum 6.

*/

int maxSum(Array* arr) {
    Array max_sum_arr;
    int counter = 0;
    int index_of_first_element = 0;
    int index_of_last_element = 0;

    int max_sum = 0;
    int currentSum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (arr->elements[i] > currentSum + arr->elements[i]) {
            currentSum = arr->elements[i];
            index_of_first_element = i;
            counter = 0;
            memset(max_sum_arr.elements, 0, sizeof(max_sum_arr.elements));
            max_sum_arr.elements[counter] = arr->elements[i];
            counter++;
            index_of_last_element = i;
        }
        else {
            currentSum = currentSum + arr->elements[i];
            int remaining_sum = 0;
            int j;
            if (index_of_last_element == 0) {
                j = i;
            }
            else {
                j = index_of_last_element;
            }
            for (; j < ARRAY_SIZE; j++) {
                remaining_sum += arr->elements[j];
            }
            if (remaining_sum > 0) {
                max_sum_arr.elements[counter] = arr->elements[i];
                counter++;
                index_of_last_element = i;
            }
        }
        max_sum = (currentSum > max_sum) ? currentSum : max_sum;
        if (i == ARRAY_SIZE - 1) {
            i = 0;
            for (; i < index_of_first_element; i++) {
                if (arr->elements[i] > 0) {
                    currentSum = currentSum + arr->elements[i];
                    max_sum_arr.elements[counter] = arr->elements[i];
                    counter++;
                    max_sum = (currentSum > max_sum) ? currentSum : max_sum;
                }
                else {
                    break;
                }
            }
            break;
        }
    }

    //----------------------------------------------------------------------------
    printf("Подмассив с наибольшей суммой: ");
    for (int i = 0; i < counter; i++) {
        printf("%d ", max_sum_arr.elements[i]);
    }
    printf("\n");

    return max_sum;
}

//--------------------------------------------------------
// Задание 4 ---------------------------------------------
//является ли дерево BST1.
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode) {
        newNode->data = data;
        newNode->left = newNode->right = NULL;
    }
    return newNode;
}

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

bool isBST(TreeNode* root, int min, int max) {
    if (root == NULL) {
        return true;
    }
    if (root->data < min || root->data > max) {
        return false;
    }
    return isBST(root->left, min, root->data) && isBST(root->right, root->data, max);
}

TreeNode* swap(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
}

//--------------------------------------------------------
// Задание 6 ---------------------------------------------
/*Пример:
"fall" и "redd" изоморфны.
"mad" и "odd" не изоморфны.
*/
bool areIsomorphic(char* str1, char* str2) {
    if (strlen(str1) != strlen(str2)) {
        return false;
    }
    HashTable ht1, ht2;
    memset(ht1.keys, 0, sizeof(ht1.keys));
    memset(ht1.values, 0, sizeof(ht1.values));
    memset(ht2.keys, 0, sizeof(ht2.keys));
    memset(ht2.values, 0, sizeof(ht2.values));

    for (int i = 0; str1[i] != '\0'; i++) {
        char ch1 = str1[i];
        char ch2 = str2[i];

        if (ht1.keys[ch1] == NULL && ht2.keys[ch2] == NULL) {
            ht1.keys[ch1] = ch2;
            ht2.keys[ch2] = ch1;
        }
        else if (ht1.keys[ch1] != ch2 || ht2.keys[ch2] != ch1) {
            return false;
        }
    }
    return true;
}

//--------------------------------------------------------
int main() {
    setlocale(LC_ALL, "Rus");
    int number = 0;
    printf("Задание 1. Стек\n");
    printf("Задание 2. Множество\n");
    printf("Задание 3. Массив\n");
    printf("Задание 4. Двоичное дерево\n");
    printf("Задание 6. Хеш-таблица\n");
    printf("Задание -1. Выход из программы\n");
    while (number != -1) {
        printf("Выберите номер задания: ");
        scanf_s("%d", &number);
        // Стек
        if (number == 1) {
            char expression[STACK_SIZE];
            printf("Введите строку: ");
            scanf_s("%s", expression, 100);
            if (isBalanced(expression) == 1) {
                printf("Скобки вложены правильно!\n");
            }
            else {
                printf("Скобки вложены неправильно!\n");
            }
            printf("\n");
        }
        // Множество
        else if (number == 2) {
            int current_number = 0;
            Set set;
            set.count = 0;
            memset(set.elements, 0, sizeof(set.elements));
            printf("Введите количество чисел в множестве: ");
            int size = 0;
            scanf_s("%d", &size);
            printf("Введите числа множества: ");
            for (int i = 0; i < size; i++) {
                scanf_s("%d", &current_number);
                SADD(&set, current_number, i);
            }
            int num_of_subsets = 0;
            printf("Введите количество подмножеств: ");
            scanf_s("%d", &num_of_subsets);
            int totalSum = sumOfSet(&set);
            if (totalSum % num_of_subsets != 0) {
                printf("Невозможно разбить множество на %d подмножеств с равной суммой.\n", num_of_subsets);
                printf("\n");
                continue;
            }
            int targetSum = totalSum / num_of_subsets;
            Set currentSet = { {0}, 0 };
            Set subsets[10];
            for (int i = 0; i < 10; i++) {
                memset(subsets[i].elements, 0, sizeof(subsets[i].elements));
                subsets[i].count = 0;
            }
            findUniqueSubsetsWithEqualSum(set, currentSet, 0, targetSum, subsets, &num_of_subsets);
            printf("\n");
        }
        // Массив
        else if (number == 3) {
            int current_number = 0;
            Array array;
            array.count = 0;
            memset(array.elements, 0, sizeof(array.elements));
            printf("Введите количество чисел в массиве: ");
            int size = 0;
            scanf_s("%d", &size);
            printf("Введите числа массива: ");
            for (int i = 0; i < size; i++) {
                scanf_s("%d", &current_number);
                AADD(&array, current_number);
            }
            int result = maxSum(&array);
            printf("Максимальная сумма подмассива: %d\n", result);
            printf("\n");
        }
        // Двоичное дерево
        else if (number == 4) {
            int current_number = 0;
            TreeNode* root = NULL;
            printf("Введите количество чисел в дереве: ");
            int size = 0;
            scanf_s("%d", &size);
            printf("Введите числа дерева: ");
            for (int i = 0; i < size; i++) {
                scanf_s("%d", &current_number);
                root = TADD(root, current_number);
            }
            //root = swap(root);
            if (isBST(root, INT_MIN, INT_MAX)) {
                printf("Дерево является бинарным поисковым деревом (BST).\n");
            }
            else {
                printf("Дерево не является бинарным поисковым деревом (BST).\n");
            }
            printf("\n");
        }
        // Хэш-таблица
        else if (number == 6) {
            char str1[100];
            char str2[100];
            printf("Введите первую строку: ");
            scanf_s("%s", &str1, sizeof(str1));
            printf("Введите вторую строку: ");
            scanf_s("%s", &str2, sizeof(str1));
            if (areIsomorphic(str1, str2)) {
                printf("Строки изоморфны.\n");
            }
            else {
                printf("Строки не изоморфны.\n");
            }
            printf("\n");
        }
        else if (number == -1) {
            return 1;
        }
    }
}
