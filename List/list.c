#include "list.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR_SIZE 30

typedef struct ListElement {
    char value[STR_SIZE];
    struct ListElement *next;
} ListElement;

typedef struct List {
    struct ListElement *head;
    struct ListElement *tail;
    int size;
} List;

List *createList(int *error) {
    struct List *list = (List *)calloc(1, sizeof(List));
    if (list == NULL) {
        *error = 1;
    } else {
        *error = 0;
    }
    return list;
}

int deleteList(List **list) {
    if (list == NULL || *list == NULL) {
        return 1;
    }
    while (!isEmpty(*list)) {
        char value[STR_SIZE] = {0};
        int errorCode = pop(list, value);
        if (errorCode != 0) {
            return 1;
        }
    }
    *list = NULL;
    return 0;
}

int pushBack(List **list, char const *value) {
    ListElement *newNode = (ListElement *)malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    strcpy(newNode->value, value);
    newNode->next = NULL;
    if ((*list)->size == 0) {
        (*list)->head = newNode;
    }
    if ((*list)->size > 0) {
        (*list)->tail->next = newNode;
    }
    (*list)->tail = newNode;
    ++(*list)->size;
    return 0;
}

int pop(List **list, char *value) {
    if (list == NULL || *list == NULL || isEmpty(*list)) {
        return 1;
    }
    ListElement *previous = (*list)->head;
    strcpy(value, previous->value);
    (*list)->head = (*list)->head->next;
    --(*list)->size;
    if ((*list)->size == 0) {
        (*list)->tail = NULL;
    }
    free(previous);
    return 0;
}

bool isEmpty(List *list) {
    return list->head == NULL;
}

int addStringsStartsWithA(List **list) {
    if (list == NULL || *list == NULL || isEmpty(*list)) {
        return 1;
    }
    ListElement *element = (*list)->head;
    int count = 0;
    int initialSize = (*list)->size;
    while (count < initialSize) {
        if (strlen(element->value) != 0 && (element->value[0] == 'a')) {
            int error = pushBack(list, element->value);
            if (error == 1) {
                return 1;
            }
        }
        ++count;
        element = element->next;
    }
    return 0;
}

int getSize(List *list) {
    if (list == NULL) {
        return -1;
    }
    return list->size;
}

int getArray(List *list, char **array, int size) {
    if (list == NULL || isEmpty(list)) {
        return 1;
    }
    int count = 0;
    ListElement *element = list->head;
    while (element != NULL && count < size) {
        strcpy(array[count], element->value);
        element = element->next;
        ++count;
    }
    return 0;
}

