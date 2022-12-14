#include "test.h"
#include "list.h"
#include <stdbool.h>
#include <string.h>

typedef struct ListElement {
    int value;
    struct ListElement *next;
} ListElement;

typedef struct List {
    struct ListElement *head;
    int size;
} List;

bool testCreate(void) {
    List *list = createList();
    if (isEmpty(list) && (list->head == NULL) && (list->size == 0)) {
        return true;
    }
    deleteList(&list);
    return false;
}

bool testPop(void) {
    List *list = createList();
    pushBack(&list, 0);
    int value = 0;
    int errorCode = pop(&list, &value);
    if (errorCode != 0) {
        deleteList(&list);
        return false;
    }
    if (value != 0) {
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

bool testIsEmpty(void) {
    List *list = createList();
    if (isEmpty(list)) {
        return true;
    }
    deleteList(&list);
    return false;
}