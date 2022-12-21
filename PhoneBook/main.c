#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct PhoneEntry {
    char name[100];
    char phone[30];
    struct PhoneEntry *next;
} PhoneEntry;

void pushBack(PhoneEntry **last, char *name, char *phone) {
    PhoneEntry *newNode = (PhoneEntry *) malloc(sizeof(PhoneEntry));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = *last;
    *last = newNode;
}

void deleteElement(PhoneEntry **last) {
    if (*last == NULL) {
        return;
    }
    PhoneEntry *previous = (*last);
    (*last) = (*last)->next;
    free(previous);
}

void deleteAll(PhoneEntry **last) {
    while ((*last) != NULL) {
        deleteElement(last);
    }
}

bool searchByName(char *name, PhoneEntry **last, char *result) {
    PhoneEntry *pointer = *last;
    while (pointer != NULL) {
        if (strcmp(pointer->name, name) == 0) {
            strcpy(result, pointer->phone);
            return true;
        }
        pointer = pointer->next;
    }
    return false;
}

bool searchByPhone(char *phone, PhoneEntry **last, char *result) {
    PhoneEntry *pointer = *last;
    while (pointer != NULL) {
        if (strcmp(pointer->phone, phone) == 0) {
            strcpy(result, pointer->name);
            return true;
        }
        pointer = pointer->next;
    }
    return false;
}

int readFile(PhoneEntry **last, char const *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("%s", "Файл не найден!");
        return 1;
    }
    while (!feof(file)) {
        char bufferName[100] = {0};
        char bufferNumber[30] = {0};
        const int readBytes = fscanf(file, "%s%s", bufferName, bufferNumber);
        if (readBytes < 0) {
            break;
        }
        pushBack(last, bufferName, bufferNumber);
    }
    fclose(file);
    return 0;
}

int writeFile(PhoneEntry **last, char const *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("%s", "Файл не найден!");
        return 1;
    }
    PhoneEntry *pointer = (*last);
    while (pointer != NULL) {
        fprintf(file, "%s %s\n", pointer->name, pointer->phone);
        pointer = pointer->next;
    }
    fclose(file);
    return 0;
}

testReadFile(void) {
    PhoneEntry *last = NULL;
    if (readFile(&last, "../testData") == 1) {
        return false;
    }
    char *correctPhones[3] = {"910-209-19-98", "819209389", "19787281987"};
    char *correctNames[3] = {"jaisoidjioa", "ajisoijdiosa", "uqioijjsioaji"};
    int index = 0;
    PhoneEntry *pointer = last;
    while (pointer != NULL) {
        if (strcmp(pointer->phone, correctPhones[index]) != 0 || strcmp(pointer->name, correctNames[index]) != 0) {
            deleteAll(&last);
            return false;
        }
        ++index;
        pointer = pointer->next;
    }
    deleteAll(&last);
    return true;
}

bool testWriteFile(void) {
    PhoneEntry *last = NULL;
    char *correctPhones[3] = {"910-209-19-98", "819209389", "19787281987"};
    char *correctNames[3] = {"jaisoidjioa", "ajisoijdiosa", "uqioijjsioaji"};
    for (int i = 0; i < 3; ++i) {
        pushBack(&last, correctNames[i], correctPhones[i]);
    }
    if (writeFile(&last, "../testWriteFile") == 1) {
        deleteAll(&last);
        return false;
    }
    FILE *file = fopen("../testWriteFile", "r");
    int index = 0;
    while (!feof(file)) {
        char bufferName[100] = {0};
        char bufferNumber[30] = {0};
        const int readBytes = fscanf(file, "%s%s", bufferName, bufferNumber);
        if (readBytes < 0) {
            break;
        }
        if (index > 2) {
            deleteAll(&last);
            fclose(file);
            return false;
        }
        if (strcmp(bufferName, correctNames[2 - index]) != 0 || strcmp(bufferNumber, correctPhones[2 - index]) != 0) {
            deleteAll(&last);
            fclose(file);
            return false;
        }
        ++index;
    }
    deleteAll(&last);
    fclose(file);
    return true;
}

bool testSearch(void) {
    PhoneEntry *last = NULL;
    readFile(&last, "../testData");
    char result[100] = {0};
    char *correctPhones[3] = {"910-209-19-98", "819209389", "19787281987"};
    char *correctNames[3] = {"jaisoidjioa", "ajisoijdiosa", "uqioijjsioaji"};
    for (int i = 0; i < 3; ++i) {
        if (!searchByPhone(correctPhones[i], &last, result) || !searchByName(correctNames[i], &last, result)) {
            deleteAll(&last);
            return false;
        }
        searchByPhone(correctPhones[i], &last, result);
        if (strcmp(correctNames[i], result) != 0) {
            deleteAll(&last);
            return false;
        }
        searchByName(correctNames[i], &last, result);
        if (strcmp(correctPhones[i], result) != 0) {
            deleteAll(&last);
            return false;
        }
    }
    deleteAll(&last);
    return true;
}

int main() {
    if (!testReadFile() || !testWriteFile() || !testSearch()) {
        printf("tests have been failed");
        return 1;
    }
    setlocale(LC_ALL, "RUS");
    printf("%s%s%s%s%s%s", "Для того, чтобы выйти, введите 0.\n",
                           "Чтобы добавить запись, введите 1.\n",
                 "Чтобы распечатать все имеющиеся записи, введите 2.\n",
                 "Чтобы найти телефон по имени, введите 3.\n",
                 "Чтобы найти имя по телефону, введите 4.\n",
                 "Сохранить текущие данные в файл, введите 5.\n");
    PhoneEntry *last = NULL;
    readFile(&last, "../data.txt");
    int commandCode = 0;
    scanf("%d", &commandCode);
    if (commandCode > 5 || commandCode < 0) {
        printf("%s", "Неверный код команды, попробуйте ввести значение еще раз.");
        return 0;
    }
    while (commandCode != 0) {
        if (commandCode == 1) {
            printf("%s", "Введите имя и номер:\n");
            char name[100] = {0};
            char phone[30] = {0};
            scanf("%s%s", name, phone);
            pushBack(&last, name, phone);

        } else if (commandCode == 2) {
            PhoneEntry *pointer = last;
            while (pointer != NULL) {
                printf("%s%s%s%s", pointer->name, " ", pointer->phone, "\n");
                pointer = pointer->next;
            }
        } else if (commandCode == 3 || commandCode == 4) {
            if (commandCode == 3) {
                printf("%s", "Please, enter the name:\n");
            } else {
                printf("%s", "Please, enter the phone:\n");
            }
            char key[100] = {0};
            scanf("%s", key);
            char result[30] = {0};
            if (commandCode == 3) {
                if (searchByName(key, &last, result)) {
                    printf("%s%s%s", "The phone number is ", result, "\n");
                } else {
                    printf("%s", "There is no such a person\n");
                }
            } else {
                if(searchByPhone(key, &last, result)) {
                    printf("%s%s%s", "The name is ", result, "\n");
                } else {
                    printf("%s", "There is no such number\n");
                }
            }
        } else {
            writeFile(&last, "../data.txt");
        }
        scanf("%d", &commandCode);
    }
    deleteAll(&last);
    return 0;
}

//0 - выйти
//1 - добавить запись (имя и телефон)
//2 - распечатать все имеющиеся записи
//3 - найти телефон по имени
//4 - найти имя по телефону
//5 - сохранить текущие данные в файл

