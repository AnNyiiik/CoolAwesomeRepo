#include "test.h"
#include "list.h"

#include <stdbool.h>
#include <stdlib.h>
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

bool testDelete(void) {
    List *list = createList();
    insert(list, 0, 0);
    insert(list, 1, 0);
    deleteList(&list);
    return isEmpty(list);
}

bool testInsert(void) {
    List *list = createList();
    insert(list, 0, 19);
    if (isEmpty(list) || list->size == 0 || list->head == NULL) {
        deleteList(&list);
        return false;
    }
    if (list->head->value != 19) {
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

bool testIsEmpty(void) {
    List *list = createList();
    if (isEmpty(list)) {
        return true;
    }
    deleteList(&list);
    return false;
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
    ListElement *element = list->head;
    for (int i = 0; i < 2; ++i) {
        if (element->value > element->next->value) {
            deleteList(&list);
            return false;
        }
    }
    deleteList(&list);
    return true;
}