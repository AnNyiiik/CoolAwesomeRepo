#include "list.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement {
    char value[30];
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
    list->tail = NULL;
    list->size = 0;
    return list;
}

int deleteList(List **list) {
    while (!isEmpty(*list)) {
        char value[30] = {0};
        int errorCode = pop(list, value);
        if (errorCode != 0) {
            return 1;
        }
    }
    *list = NULL;
    return 0;
}

int pushBack(List **list, char const *value) {
    ListElement *newNode = (ListElement *) malloc(sizeof(ListElement));
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
    if (isEmpty(*list)) {
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
    if (list == NULL || isEmpty(*list)) {
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
void getArray(List *list, char *array) {
    if (isEmpty(list)) {
        printf("List is empty\n");
    }
    int count = 0;
    ListElement *element = list->head;
    while (element != NULL) {
        array[count] = element->value;
        element = element->next;
        ++count;
    }
}

