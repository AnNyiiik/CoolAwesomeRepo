#include "test.h"
#include "list.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 30

bool testCreate(void) {
    List *list = createList();
    if (list == NULL) {
        return false;
    }
    if (isEmpty(list)) {
        return true;
    }
    deleteList(&list);
    return false;
}

bool testDelete(void) {
    List *list = createList();
    pushBack(&list, "a");
    deleteList(&list);
    return list == NULL;
}

bool testPushBack(void) {
    List *list = createList();
    pushBack(&list, "a");
    if (list == NULL) {
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
    List *list = createList();
    int errorCode = pushBack(&list, "a");
    if (errorCode != 0) {
        deleteList(&list);
        return false;
    }
    char value[STR_SIZE] = {0};
    errorCode = pop(&list, value);
    if (errorCode != 0) {
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
    List *list = createList();
    int error = pushBack(&list, "a");
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
    char ** array = (char**)malloc(sizeof(char*) * getSize(list));
    if (array == NULL) {
        return 1;
    }
    for (int i = 0; i < getSize(list); i++) {
        array[i] = (char*)malloc(sizeof(int) * STR_SIZE);
        if (array[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free (array[j]);
            }
            free(array);
            return 1;
        }
    }
    getArray(list, array);
    for (int i = 0; i < getSize(list); ++i) {
        if (strcmp(array[i], correctSequence[i]) != 0) {
            deleteList(&list);
            for (int j = 0; j < getSize(list); ++j) {
                free(array[j]);
            }
            free(array);
            return false;
        }
    }
    for (int j = 0; j < getSize(list); ++j) {
        free(array[j]);
    }
    free(array);
    deleteList(&list);
    return true;
}

bool testIsEmpty(void) {
    List *list = createList();
    if (isEmpty(list)) {
        return true;
    }
    deleteList(&list);
    return false;
}
