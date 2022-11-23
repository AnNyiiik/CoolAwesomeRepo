#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement {
    int value;
    struct ListElement *next;
    struct ListElement *previous;
} ListElement;

typedef struct List {
    struct ListElement *head;
    struct ListElement *tail;
    int size;
} List;

List *createList(void) {
    struct List *list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int deleteList(List **list) {
    while (!isEmpty(*list)) {
        int value = 0;
        int errorCode = pop(list, &value);
        if (errorCode != 0) {
            return 1;
        }
    }
    return 0;
}

int pushFront(List **list, int value) {
    ListElement *newNode = (ListElement *) malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    newNode->value = value;
    newNode->next = (*list)->head;
    newNode->previous = NULL;
    if ((*list)->head) {
        (*list)->head->previous = newNode;
    }
    if ((*list)->size == 0) {
        (*list)->tail = newNode;
    }
    (*list)->head = newNode;
    ++(*list)->size;
    return 0;
}

int pop(List **list, int *value) {
    if (isEmpty(list)) {
        return 1;
    }
    ListElement *deleted = (*list)->head;
    *value = (deleted)->value;
    if (((*list)->head)->next) {
        ((*list)->head)->previous = NULL;
    }
    ((*list)->head) = ((*list)->head)->next;
    --(*list)->size;
    free(deleted);
    return 0;
}

bool checkSymmetric(List *list) {
    ListElement *elementEnd = list->tail;
    ListElement *elementStart = list->head;
    for (int i = 0; i < list->size / 2; ++i) {
        if (elementEnd->value != elementStart->value) {
            return false;
        }
        elementStart = elementStart->next;
        elementEnd = elementEnd->previous;
    }
    return true;
}

bool isEmpty(List *list) {
    return list->head == NULL;
}

