#include "list.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement {
    int value;
    struct Node *next;
} ListElement;

typedef struct List {
    ListElement *head;
} List;

List *createList(void) {
    struct List *list = (List *) malloc(sizeof(List));
    list->head = NULL;
    return list;
}

int deleteStack(List **list) {
    while (!isEmpty(*list)) {
        int value = 0;
        int errorCode = pop(list, &value);
        if (errorCode != 0) {
            return 1;
        }
    }
    return 0;
}

int push(List **list, int value) {
    ListElement *newNode = (ListElement *) malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    newNode->value = value;
    newNode->next = (*list)->head;
    (*list)->head = newNode;
    return 0;
}

int pop(List **list, int *value) {
    if (list == NULL) {
        return 1;
    }
    ListElement *previous = (*list)->head;
    *value = (previous)->value;
    ((*list)->head) = ((*list)->head)->next;
    free(previous);
    return 0;
}

bool isEmpty(List *list) {
    return list->head == NULL;
}

