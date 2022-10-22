#include "list.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement {
    int value;
    struct ListElement *next;
} ListElement;

typedef struct List {
    struct ListElement *head;
} List;

List *createList(void) {
    struct List *list = (List *) malloc(sizeof(List));
    list->head = NULL;
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

int insert(List *list, int place, int value) {
    if (place == 0) {
        push(&list, value);
        return 0;
    }
    int index = 0;
    ListElement *element = list->head;
    while (index < place - 1 && element->next) {
        element = element->next;
        ++index;
    }
    ListElement *newElement = (ListElement *) malloc(sizeof(ListElement));
    newElement->value = value;
    if (element->next) {
        newElement->next = element->next;
    } else {
        newElement->next = NULL;
    }
    element->next = newElement;
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

