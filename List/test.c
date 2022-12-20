#include "test.h"
#include "list.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool testCreate(void) {
    List *list = createList();
    if (isEmpty(list)) {
        deleteList(&list);
        return true;
    }
    deleteList(&list);
    return false;
}

bool testDelete(void) {
    List *list = createList();
    insert(list, 0, 0);
    insert(list, 1, 0);
    deleteList(&list);
    return list == NULL;
}

bool testInsert(void) {
    List *list = createList();
    insert(list, 0, 19);
    if (isEmpty(list)) {
        deleteList(&list);
        return false;
    }
    int returnValue = 0;
    pop(&list, &returnValue);
    if (returnValue != 19) {
        deleteList(&list);
        return false;
    }
    deleteList(&list);
    return true;
}

bool testPop(void) {
    List *list = createList();
    insert(list, 0, 16);
    int value = 0;
    int errorCode = pop(&list, &value);
    if (errorCode != 0) {
        deleteList(&list);
        return false;
    }
    if (value != 16) {
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

bool testInsertByOrder(void) {
    List *list = createList();
    for (int i = 0; i < 3; ++i) {
        int errorCode= insertByOrder(list, rand() % 10);
        if (errorCode != 0) {
            deleteList(&list);
            return false;
        }
    }
    int returnValue = 0;
    pop(&list, &returnValue);
    while (!isEmpty(list)) {
        int nextValue = 0;
        pop(&list, &nextValue);
        if (nextValue < returnValue) {
            deleteList(&list);
            return false;
        }
        returnValue = nextValue;
    }
    deleteList(&list);
    return true;
}