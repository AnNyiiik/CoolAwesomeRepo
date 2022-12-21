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

List *createList(int *error) {
    List *list = (List *)calloc(sizeof(List));
    if (list == NULL) {
        *error = 1;
        return NULL;
    }
    *error = 0;
    return list;
}

void tryAdd(List **list, char *word, bool *isNew, int frequency) {
    if (list == NULL || *list == NULL || isEmpty(*list)) {
        return;
    }
    ListElement *element = (*list)->head;
    *isNew = false;
    while (element != NULL) {
        if (strcmp(element->word, word) == 0) {
            element->frequency += frequency;
            *isNew = true;
            break;
        }
        element = element->next;
    }

int deleteList(List **list) {
    while (!isEmpty(*list)) {
        int value = 0;
        int path = 0;
        int errorCode = pop(list, &value, &path);
        if (errorCode != 0) {
            return 1;
        }
    }
    *list = NULL;
    return 0;
}

int getHeadFrequency(List *list) {
    if (list != NULL) {
        return list->head->frequency;
    }
    else {
        return -1;
    }
}

int getFrequency(char *word, List *list) {
    if (list == NULL || isEmpty(list)) {
        return 0;
    }
    ListElement *element = list->head;
    while (element != NULL) {
        if (strcmp(element->word, word) == 0) {
            return element->frequency;
        }
        element = element->next;
    }
    return 0;
}

int getSize(List *list) {
    if (list != NULL) {
        return list->size;
    }
    else {
        return -1;


int getHead(List *list, char *value) {
    if (list != NULL && !isEmpty(list)) {
        strcpy(value, list->head->word);
        return 0;
    }
    return 1;
}

int deleteList(List **list) {
    if (list == NULL || *list == NULL) {
        return 1;
    }
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
    ListElement *newNode = (ListElement *)malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    newNode->frequency = frequency;
    newNode->word = (char *)malloc(sizeof(word) + 1);
    strcpy(newNode->word, word);
    newNode->word[sizeof(word)] = '\0';
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
    if (isEmpty(*list)) {
        return 1;
    }
    ListElement *previous = (*list)->head;
    ((*list)->head) = ((*list)->head)->next;
    --(*list)->size;
    free(previous->word);
    free(previous);
    return 0;
}

void delete(char *word, List **list) {
    if (isEmpty(*list)) {
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
}

bool isEmpty(List *list) {
    if (list == NULL) {
        return true;
    }
    return list->head == NULL;
}

void printList(List *list) {
    if (list == NULL || isEmpty(list)) {
        return;
    }
    ListElement *element = list->head;
    while(element != NULL) {
        printf("%s - %d\n", element->word, element->frequency);
        element = element->next;
    }
}
