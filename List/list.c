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
        int errorCode = pop(list);
        if (errorCode != 0) {
            return 1;
        }
    }
    (*list) = NULL;
    return 0;
}

int push(List **list, int frequency, char *word) {
    ListElement *newNode = (ListElement *) malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    newNode->frequency = frequency;
    newNode->word = (char *) malloc(sizeof(word));
    strcpy(newNode->word, word);
    if ((*list)->head) {
        (*list)->tail->next = newNode;
        newNode->next = NULL;
        (*list)->tail = newNode;
    } else {
        newNode->next = NULL;
        (*list)->head = newNode;
        (*list)->tail = newNode;
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

void delete(char *word, List **list) {
    if (isEmpty(list)) {
        return;
    }
    ListElement *element = (*list)->head;
    ListElement *previous = (*list)->head;
    while (element != NULL && strcmp(element->word, word) != 0) {
        previous = element;
        element = element->next;
    }
    if (element == NULL) {
        return;
    }
    if (element == previous) {
        pop(list);
        return;
    }
    previous->next = element->next;
    free(element->word);
    free(element);
    --(*list)->size;
    return;
}

bool isEmpty(List *list) {
    return list->head == NULL;
}
