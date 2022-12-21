#include "test.h"
#include "list.h"

#include <stdbool.h>
#include <string.h>

bool testCreate(void) {
    int error = 0;
    List *list = createList(&error);
    if (list == NULL) {
        return false;
    }
    bool answer = isEmpty(list);
    deleteList(&list);
    return answer;
}

bool testPop(void) {
    int error = 0;
    List *list = createList(&error);
    if (list == NULL) {
        return false;
    }
    push(&list, 5);
    int value = 0;
    error = pop(&list, &value);
    if (error != 0) {
        deleteList(&list);
        return false;
    }
    if (value != 5) {
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

bool testPush(void) {
    int error = 0;
    List *list = createList(&error);
    if (list == NULL) {
        return false;
    }
    push(&list, 5);
    bool answer = !(isEmpty(list));
    deleteList(&list);
    return answer;
}

bool testDelete(void) {
    int error = 0;
    List *list = createList(&error);
    if (list == NULL) {
        return false;
    }
    for (int i = 0; i < 11; ++i) {
        push(&list, 5);
    }
    error = deleteList(&list);
    if (error == 1) {
        return false;
    }
    return (isEmpty(list) && list == NULL);
}

bool testDeleteOdd(void) {
    int error = 0;
    List *list = createList(&error);
    if (error == 1) {
        deleteList(&list);
        return false;
    }
    for (int i = 5; i > 0; --i) {
        error = push(&list, i);
        if (error == 1) {
            deleteList(&list);
            return false;
        }
    }
    error = deleteOddPositions(&list);
    if (error == 1) {
        deleteList(&list);
        return false;
    }
    int correctValues[3] = {1, 3, 5};
    for (int i = 0; i < 3; ++i) {
        int value = 0;
        error = pop(&list, &value);
        if (error == 1) {
            deleteList(&list);
            return false;
        }
        if (value != correctValues[i]) {
            deleteList(&list);
            return false;
        }
    }
    bool answer = isEmpty(list);
    deleteList(&list);
    return answer;
}

bool test(void) {
    return (testCreate() && testPop() && testDelete() && testPush() && testDeleteOdd());
}