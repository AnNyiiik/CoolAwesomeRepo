#include "sort.h"
#include <string.h>
#include <stdio.h>
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

int deleteList(List *list) {
    while (!isEmpty(list)) {
        int errorCode = pop(&list);
        if (errorCode != 0) {
            return 1;
        }
    }
    return 0;
}

int pushBack(List **list, char *name, char *phone) {
    ListElement *newNode = (ListElement *) malloc(sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    newNode->name = name;
    newNode->phone = phone;
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

int pop(List **list) {
    if (isEmpty(*list)) {
        return 0;
    }
    ListElement *previous = (*list)->head;
    ((*list)->head) = ((*list)->head)->next;
    if (previous == (*list)->tail) {
        (*list)->tail = NULL;
    }
    free(previous);
    return 0;
}

bool isEmpty(List *list) {
    return (list->head == NULL) && (list->tail == NULL);
}

ListElement *merge(ListElement *halfFirst, ListElement *halfSecond, int key) {
    if (halfFirst == NULL) {
        return halfSecond;
    }
    else if (halfSecond == NULL) {
        return halfFirst;
    }
    ListElement *result = NULL;
    int compare = 0;
    if (key == 0) {
        compare = strcmp(halfFirst->name, halfSecond->name);
    } else {
        compare = strcmp(halfFirst->phone, halfSecond->phone);
    }
    if (compare <= 0) {
        result = halfFirst;
        result->next = merge(halfFirst->next, halfSecond, key);
    } else {
        result = halfSecond;
        result->next = merge(halfFirst, halfSecond->next, key);
    }
    return result;
}

void divide(ListElement *full, ListElement **first, ListElement **second) {
    if (full == NULL || full->next == NULL)
    {
        *first = full;
        *second = NULL;
        return;
    }
    ListElement *ptr1 = full;
    ListElement *ptr2 = full->next;
    while (ptr2 != NULL)
    {
        ptr2 = ptr2->next;
        if (ptr2 != NULL)
        {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    *first = full;
    *second = ptr1->next;
    ptr1->next = NULL;
}

void mergeSort(ListElement **head, int key) {
    if ((*head) == NULL || (*head)->next == NULL) {
        return;
    }
    ListElement *firstHalf = NULL;
    ListElement *secondHalf = NULL;
    divide(*head, &firstHalf, &secondHalf);
    mergeSort(&firstHalf, key);
    mergeSort(&secondHalf, key);
    *head = merge(firstHalf, secondHalf, key);
}

void sort(List **list, int key) {
    mergeSort(&((*list)->head), key);
    ListElement *tail = (*list)->head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    (*list)->tail = tail;
}

void printList(List *list) {
    ListElement *element = list->head;
    while (element != NULL) {
        printf("%s%s%s%s", element->name, " ", element->phone, "\n");
        element = element->next;
    }
    return;
}






