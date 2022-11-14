#include "list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement {
    int frequency;
    char *word;
    struct ListElement *next;
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
        int errorCode = pop(list);
        if (errorCode != 0) {
            return 1;
        }
    }
    return 0;
}

int delete(List *list, int place) {
    if (place > list->size - 1) {
        return 1;
    }
    if (isEmpty(list)) {
        return 1;
    }
    if (place == 0) {
        int errorCode = pop(&list);
        if (errorCode != 0) {
            return 1;
        }
        return 0;
    }
    int index = 0;
    ListElement *element = list->head;
    while (index < place - 1 && element->next) {
        element = element->next;
        ++index;
    }
    if (element->next) {
        if (element->next->next) {
            ListElement *elementAfterDeleted = element->next->next;
            free(element->next->word);
            free(element->next);
            element->next = elementAfterDeleted;
            --list->size;
            return 0;
        } else {
            free(element->next->word);
            free(element->next);
        }
        element->next = NULL;
        --list->size;
        return 0;
    }
    return 0;
}

int getElementPlace(List *list, char *word) {
    if (isEmpty(list)) {
        return -1;
    }
    ListElement *element = list->head;
    int place = 0;
    while (element->next) {
        if (strcmp(word, element->word)) {
            return place;
        }
        element = element->next;
        ++place;
    }
    return -1;
}

int push(List **list, int frequency, char *word) {
    ListElement *newNode = (ListElement *) malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    newNode->frequency = frequency;
    newNode = (char *) malloc(sizeof(word));
    strcpy(newNode->word, word);
    if ((*list)->head) {
        (*list)->tail->next = newNode;
        newNode->next = NULL;
        (*list)->tail = newNode;
    } else {
        newNode->next = NULL;
        (*list)->head = newNode;
    }
    ++(*list)->size;
    return 0;
}

int pop(List **list) {
    if (isEmpty(list)) {
        return 0;
    }
    ListElement *previous = (*list)->head;
    ((*list)->head) = ((*list)->head)->next;
    --(*list)->size;
    free(previous->word);
    free(previous);
    return 0;
}

bool isEmpty(List *list) {
    return list->head == NULL;
}
