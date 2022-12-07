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
    struct ListElement *tail;
    int size;
} List;

List *createList(void) {
    struct List *list = (List *)calloc(1, sizeof(List));
    list->head = NULL;
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

int pushBack(List **list, int value) {
    ListElement *newNode = (ListElement *)malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    newNode->value = value;
    newNode->next = NULL;
    if ((*list)->size == 0) {
        (*list)->head = newNode;
    }else {
        (*list)->tail->next = newNode;
    }
    (*list)->tail = newNode;
    ++(*list)->size;
    return 0;
}

int pop(List **list, int *value) {
    if (isEmpty(*list)) {
        return 1;
    }
    ListElement *previous = (*list)->head;
    *value = previous->value;
    (*list)->head = (*list)->head->next;
    --(*list)->size;
    free(previous);
    return 0;
}

List *makeOne(List *listFirst, List *listSecond) {
    if (listFirst == NULL) {
        return listSecond;
    } else if (listSecond == NULL) {
        return listFirst;
    }
    List *list = createList();
    ListElement *element = listFirst->head;
    for (int i = 0; i < listFirst->size; ++i) {
        pushBack(&list, element->value);
        element = element->next;
    }
    element = listSecond->head;
    for (int i = 0; i < listSecond->size; ++i) {
        pushBack(&list, element->value);
        element = element->next;
    }
    return list;
}

bool isEmpty(List *list) {
    return list->head == NULL;
}

void printList(List *list, char const *path) {
    if (isEmpty(list)) {
        printf("List is empty\n");
    }
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        return;
    }
    ListElement *element = list->head;
    while (element != NULL) {
        fprintf(file, "%d ", element->value);
        element = element->next;
    }
    fclose(file);
}