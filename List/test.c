#include "test.h"
#include "list.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 30

bool testCreate(void) {
    int error = 0;
    List *list = createList(&error);
    if (error == 1) {
        return false;
    }
    if (isEmpty(list)) {
        return true;
    }
    deleteList(&list);
    return false;
}

bool testDelete(void) {
    int error = 0;
    List *list = createList(&error);
    if (error == 1) {
        return false;
    }
    error = pushBack(&list, "a");
    if (error == 1) {
        return false;
    }
    deleteList(&list);
    return list == NULL;
}

bool testPushBack(void) {
    int error = 0;
    List *list = createList(&error);
    if (error == 1) {
        return false;
    }
    error = pushBack(&list, "a");
    if (list == NULL) {
        return false;
    }
    if (error == 1) {
        deleteList(&list);
        return false;
    }
    if (isEmpty(list)) {
        deleteList(&list);
        return false;
    }
    deleteList(&list);
    return true;
}

bool testPop(void) {
    int error = 0;
    List *list = createList(&error);
    if (error == 1) {
        return false;
    }
    error = pushBack(&list, "a");
    if (error == 1) {
        deleteList(&list);
        return false;
    }
    char value[STR_SIZE] = {0};
    error = pop(&list, value);
    if (error != 0) {
        deleteList(&list);
        return false;
    }
    if (strcmp(value, "a") != 0) {
        deleteList(&list);
        return false;
    }
    if (!isEmpty(list)) {
        deleteList(&list);
        return false;
    }
    deleteList(&list);
    return true;
}

bool testAddA(void) {
    int error = 0;
    List *list = createList(&error);
    if (error == 1) {
        return false;
    }
    error = pushBack(&list, "a");
    if (error == 1) {
        deleteList(&list);
        return false;
    }
    error = pushBack(&list, "b");
    if (error == 1) {
        deleteList(&list);
        return false;
    }
    error = pushBack(&list, "c");
    if (error == 1) {
        deleteList(&list);
        return false;
    }
    error = addStringsStartsWithA(&list);
    if (error == 1) {
        deleteList(&list);
        return false;
    }
    char *correctSequence[4] = {"a", "b", "c", "a"};
    int arraySize = getSize(list);
    if (arraySize == -1) {
        deleteList(&list);
        return false;
    }
    char ** array = (char**)malloc(sizeof(char*) * arraySize);
    if (array == NULL) {
        return false;
    }
    for (int i = 0; i < arraySize; i++) {
        array[i] = (char*)malloc(sizeof(int) * STR_SIZE);
        if (array[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free (array[j]);
            }
            free(array);
            deleteList(&list);
            return false;
        }
    }
    getArray(list, array, arraySize);
    for (int i = 0; i < arraySize; ++i) {
        if (strcmp(array[i], correctSequence[i]) != 0) {
            deleteList(&list);
            for (int j = 0; j < arraySize; ++j) {
                free(array[j]);
            }
            free(array);
            deleteList(&list);
            return false;
        }
    }
    for (int j = 0; j < arraySize; ++j) {
        free(array[j]);
    }
    free(array);
    deleteList(&list);
    return true;
}

bool testIsEmpty(void) {
    int error = 0;
    List *list = createList(&error);
    if (error == 1) {
        return false;
    }
    if (isEmpty(list)) {
        deleteList(&list);
        return true;
    }
    deleteList(&list);
    return false;
}
