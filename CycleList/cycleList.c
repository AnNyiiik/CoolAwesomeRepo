#include "cycleList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement {
    int index;
    int value;
    struct ListElement *next;
} ListElement;

typedef struct List {
    struct ListElement *head;
    struct ListElement *tail;
} List;

List *createList(void) {
    struct List *list = (List *)calloc(1, sizeof(List));
    return list;
}

int deleteList(List **list) {
    while (!isEmpty(*list)) {
        int errorCode = pop(list);
        if (errorCode != 0) {
            return 1;
        }
    }
    free(*list);
    *list = NULL;
    return 0;
}

void delete(List **list, ListElement **elementBeforeDeleted) {
    if ((*elementBeforeDeleted) == NULL) {
        return;
    }
    if ((*list)->head == (*list)->tail) {
        free(*elementBeforeDeleted);
        (*list)->head = NULL;
        (*list)->tail = NULL;
        return;
    }
    if ((*elementBeforeDeleted)->next == (*list)->head) {
        (*list)->head = (*elementBeforeDeleted)->next->next;
    }
    if ((*elementBeforeDeleted)->next == (*list)->tail) {
        (*list)->tail = (*elementBeforeDeleted);
    }
    ListElement *elementAfterDeleted = (*elementBeforeDeleted)->next->next;
    free((*elementBeforeDeleted)->next);
    (*elementBeforeDeleted)->next = elementAfterDeleted;
}

int pushBack(List **list, int value) {
    ListElement *newNode = (ListElement *) malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    if (isEmpty(*list)) {
        newNode->value = value;
        newNode->index = 1;
        newNode->next = newNode;
        (*list)->head = newNode;
        (*list)->tail = newNode;
        return 0;
    }
    newNode->value = value;
    newNode->index = (*list)->tail->index + 1;
    newNode->next = (*list)->head;
    (*list)->tail->next = newNode;
    (*list)->tail = newNode;
    return 0;
}

ListElement *getHead(List *list) {
    if (list == NULL) {
        return NULL;
    }
    return list->head;
}

ListElement *getNext(ListElement *element) {
    if (element == NULL) {
        return NULL;
    }
    return element->next;
}

int pop(List **list) {
    if (isEmpty(*list)) {
        return 1;
    }
    if ((*list)->head == (*list)->tail) {
        free((*list)->head);
        (*list)->head = NULL;
        (*list)->tail = NULL;
        return 0;
    }
    ListElement *previous = (*list)->head;
    ((*list)->tail->next) = ((*list)->head)->next;
    ((*list)->head) = ((*list)->head)->next;
    free(previous);
    return 0;
}

bool isEmpty(List *list) {
    if (list == NULL) {
        return true;
    }
    return list->head == NULL;
}

int getIndexFirst(List *list) {
    if (list->head == NULL) {
        return -1;
    }
    return list->head->index;
}

