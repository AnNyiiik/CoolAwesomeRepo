#include "list.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement {
    char *name;
    char *phone;
    struct ListElement *next;
} ListElement;

typedef struct List {
    ListElement *head;
    ListElement *tail;
} List;

List *createList(void) {
    struct List *list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int deleteList(List **list) {
    if (*list == NULL) {
        return 1;
    }
    while (!isEmpty(*list)) {
        int errorCode = pop(list);
        if (errorCode != 0) {
            return 1;
        }
    }
    free(*list);
    *list = NULL;
    return 0;
}

int pushBack(List **list, char *name, char *phone) {
    ListElement *newNode = (ListElement *) malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    newNode->name = (char*) malloc(sizeof(char) * 100);
    strcpy(newNode->name, name);
    newNode->phone = (char*) malloc(sizeof(char) * 30);
    strcpy(newNode->phone, phone);
    newNode->next = NULL;
    if (isEmpty(*list)) {
        (*list)->head = newNode;
        (*list)->tail = newNode;
        return 0;
    }
    (*list)->tail->next = newNode;
    (*list)->tail = newNode;
    return 0;
}

char *getHeadName(List *list) {
    if (list == NULL) {
        return NULL;
    }
    return list->head->name;
}

char *getHeadPhone(List *list) {
    if (list == NULL) {
        return NULL;
    }
    return list->head->phone;
}

char *getTailName(List *list) {
    if (list == NULL) {
        return NULL;
    }
    return list->tail->name;
}

char *getTailPhone(List *list) {
    if (list == NULL) {
        return NULL;
    }
    return list->tail->phone;
}

int pop(List **list) {
    if (isEmpty(*list)) {
        return 0;
    }
    ListElement *previous = (*list)->head;
    ((*list)->head) = ((*list)->head)->next;
    if (previous == (*list)->tail) {
        (*list)->tail = NULL;
    }
    free(previous->name);
    free(previous->phone);
    free(previous);
    return 0;
}

bool isLessFirst(List *headFirst, List *headSecond, int key) {
    if (key == 0) {
        return (strcmp(headFirst->head->name, headSecond->head->name) < 0);
    } else {
        return (strcmp(headFirst->head->phone, headSecond->head->phone) < 0);
    }
}

void divide(List *full, List **first, List **second) {
    if (isOneElementSize(full)) {
        *first = full;
        *second = NULL;
        return;
    }
    ListElement *pointerFirst = full->head;
    ListElement *pointerSecond = pointerFirst->next;
    while (pointerSecond != NULL) {
        pointerSecond = pointerSecond->next;
        if (pointerSecond != NULL) {
            pointerFirst = pointerFirst->next;
            pointerSecond = pointerSecond->next;
        }
    }
    *first = full;
    (*first)->tail = pointerFirst;
    *second = createList();
    (*second)->head = pointerFirst->next;
    pointerFirst->next = NULL;
}

bool isEmpty(List *list) {
    if (list == NULL) {
        return true;
    }
    return list->head == NULL;
}

bool isOneElementSize(List *list) {
    if (list == NULL) {
        return false;
    }
    return list->head && !(list->head->next);
}

void printList(List *list) {
    ListElement *element = list->head;
    while (element != NULL) {
        printf("%s%s%s%s", element->name, " ", element->phone, "\n");
        element = element->next;
    }
    return;
}

bool isEqualLists(List *first, List *second) {
    if (first == NULL && second == NULL) {
        return true;
    }
    if (first == NULL) {
        return false;
    }
    if (second == NULL) {
        return false;
    }
    ListElement *pointerFirst = first->head;
    ListElement *pointerSecond = second->head;
    while (pointerFirst != NULL && pointerSecond != NULL) {
        if (strcmp(pointerFirst->phone, pointerSecond->phone) == 0 &&
        strcmp(pointerFirst->name, pointerSecond->name) == 0) {
            pointerSecond = pointerSecond->next;
            pointerFirst = pointerFirst->next;
            continue;
        } else {
            return false;
        }
    }
    return pointerFirst == NULL && pointerSecond == NULL;
}