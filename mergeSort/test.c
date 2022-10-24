#include "test.h"
#include "sort.h"
#include <stdlib.h>
#include <string.h>

typedef struct ListElement {
    char *name;
    char *phone;
    struct ListElement *next;
} ListElement;

typedef struct List {
    ListElement *head;
    ListElement *tail;
} List;

bool testCreate(void) {
    List *list = createList();
    if (isEmpty(list)) {
        return true;
    }
    deleteList(list);
    return false;
}

bool testDelete(void) {
    List *list = createList();
    pushBack(&list, "A", "456");
    pushBack(&list, "N", "407");
    deleteList(list);
    if (isEmpty(list)) {
        return true;
    }
    return false;
}

bool testPushBack(void) {
    List *list = createList();
    pushBack(&list, "A", "456");
    if (isEmpty(list)) {
        deleteList(list);
        return false;
    }
    deleteList(list);
    return true;
}

bool testPop(void) {
    List *list = createList();
    pushBack(&list, "A", "456");
    pop(&list);
    if (!isEmpty(list)) {
        deleteList(list);
        return false;
    }
    deleteList(list);
    return true;
}

bool testIsEmpty(void) {
    List *list = createList();
    if (isEmpty(list)) {
        return true;
    }
    deleteList(list);
    return false;
}

bool testSort(void) {
    List *listCorrectSequence = createList();
    pushBack(&listCorrectSequence, "B", "8906");
    pushBack(&listCorrectSequence, "G", "9018");
    pushBack(&listCorrectSequence, "W", "7896");
    List *list = createList();
    pushBack(&list, "W", "7896");
    pushBack(&list, "B", "8906");
    pushBack(&list, "G", "9018");
    sort(&list, 0);
    ListElement *answerElement = list->head;
    ListElement *correctElement = listCorrectSequence->head;
    for (int i = 0; i < 3; ++i) {
        if(strcmp(answerElement->name, correctElement->name) != 0) {
            deleteList(list);
            deleteList(listCorrectSequence);
            return false;
        }
    }
    deleteList(list);
    deleteList(listCorrectSequence);
    pushBack(&list, "G", "9018");
    pushBack(&list, "W", "7896");
    pushBack(&list, "B", "8906");
    pushBack(&listCorrectSequence, "W", "7896");
    pushBack(&listCorrectSequence, "B", "8906");
    pushBack(&listCorrectSequence, "G", "9018");
    sort(&list, 1);
    answerElement = list->head;
    correctElement = listCorrectSequence->head;
    for (int i = 0; i < 3; ++i) {
        if(strcmp(answerElement->phone, correctElement->phone) != 0) {
            deleteList(list);
            deleteList(listCorrectSequence);
            return false;
        }
    }
    deleteList(list);
    deleteList(listCorrectSequence);
    return true;
}