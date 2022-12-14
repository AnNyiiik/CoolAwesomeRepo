#include "test.h"
#include "list.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
    if (isEmpty(list)) {
        deleteList(&list);
        return false;
    }
    deleteList(&list);
    return true;
}

bool testPop(void) {
    List *list = createList();
    pushBack(&list, "a");
    char value[30] = {0};
    int errorCode = pop(&list, value);
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
    addStringsStartsWithA(&list);
    char *correctSequence[4] = {"a", "b", "c", "a"};

    char *array[4] = {0};
    getArray(list, array);
    for (int i = 0; i < 4; ++i) {
        if (strcmp(array[i], correctSequence[i]) != 0) {
            deleteList(&list);
            return false;
        }
    }
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
