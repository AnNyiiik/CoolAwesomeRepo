#include "test.h"
#include "list.h"

#include <stdbool.h>
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
    pushBack(&list, "A", "456");
    pushBack(&list, "N", "407");
    deleteList(&list);
    if (isEmpty(list)) {
        return true;
    }
    return false;
}

bool testPushBack(void) {
    List *list = createList();
    pushBack(&list, "A", "456");
    if (isEmpty(list)) {
        deleteList(&list);
        return false;
    }
    char *phone = getTailPhone(list);
    char *name = getTailName(list);
    if (strcmp(phone, "456") != 0 || strcmp(name, "A") != 0) {
        deleteList(&list);
        return false;
    }
    deleteList(&list);
    return true;
}

bool testPop(void) {
    List *list = createList();
    pushBack(&list, "A", "456");
    pop(&list);
    if (!isEmpty(list)) {
        deleteList(&list);
        return false;
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