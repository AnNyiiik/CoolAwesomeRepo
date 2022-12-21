#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement {
    int value;
    struct ListElement *next;
} ListElement;

typedef struct List {
    struct ListElement *head;
    int size;
} List;

List *createList(int *error) {
    *error = 0;
    struct List *list = (List *)calloc(1, sizeof(List));
    if (list == NULL) {
        *error = 1;
        return NULL;
    }
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
    free(*list);
    *list = NULL;
    return 0;
}

int push(List **list, int value) {
    ListElement *newNode = (ListElement *)calloc(1, sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    newNode->value = value;
    newNode->next = (*list)->head;
    (*list)->head = newNode;
    ++(*list)->size;
    return 0;
}

int pop(List **list, int *value) {
    if (list == NULL || *list == NULL || isEmpty(*list)) {
        return 1;
    }
    ListElement *previous = (*list)->head;
    *value = previous->value;
    (*list)->head = (*list)->head->next;
    --(*list)->size;
    free(previous);
    return 0;
}

bool isEmpty(List *list) {
    if (list == NULL) {
        return true;
    }
    return list->head == NULL;
}

int deleteOddPositions(List **list) {
    if (list == NULL || *list == NULL || isEmpty(*list)) {
        return 1;
    }
    ListElement *previous = (*list)->head;
    ListElement *element = previous->next;
    while (element != NULL) {
        previous->next = element->next;
        free(element);
        --(*list)->size;
        previous = previous->next;
        element = previous->next;
    }
    return 0;
}