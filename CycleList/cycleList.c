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
    struct List *list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int deleteList(List *list) {
    while (!isEmpty(list)) {
        int errorCode = pop(&list);
        if (errorCode != 0) {
            return 1;
        }
    }
    return 0;
}

void delete(List *list, int place) {
    if (isEmpty(list)) {
        return;
    }
    if (place == 0) {
        int errorCode = pop(&list);
        if (errorCode != 0) {
            return;
        }
        return;
    }
    int index = 0;
    ListElement *element = list->head;
    while (index < place - 1) {
        element = element->next;
        ++index;
    }
    ListElement *elementAfterDeleted = element->next->next;
    if (element->next == list->head) {
        list->tail->next = elementAfterDeleted;
        list->head = elementAfterDeleted;
    } else if (element->next == list->tail) {
        list->tail = element;
    }
    free(element->next);
    element->next = elementAfterDeleted;
    return;
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

int pop(List **list) {
    if (isEmpty(*list)) {
        return 0;
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

int getIndex(List *list) {
    return list->head->index;
}

bool isEmpty(List *list) {
    return list->head == NULL;
}

