#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement {
    int number;
    int path;
    struct ListElement *next;
} ListElement;

typedef struct List {
    struct ListElement *head;
    int size;
} List;

List *createList(int *error) {
    List *list = (List *)calloc(1, sizeof(List));
    if (list == NULL) {
        *error = 1;
    } else {
        *error = 0;
    }
    return list;
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

int delete(List *list, int place) {
    if (place > list->size - 1) {
        return 1;
    }
    if (isEmpty(list)) {
        return 1;
    }
    if (place == 0) {
        int value = 0;
        int path = 0;
        int errorCode = pop(&list, &value, &path);
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
            free(element->next);
            element->next = elementAfterDeleted;
            --list->size;
            return 0;
        }
        free(element->next);
        element->next = NULL;
        --list->size;
        return 0;
    }
    --list->size;
    return 0;
}

int getPath(List *list, int number) {
    if (isEmpty(list)) {
        return -1;
    }
    ListElement *element = list->head;
    while (element->next) {
        if (element->number == number) {
            return element->path;
        }
        element = element->next;
    }
    return -1;
}

int getElementPlace(List *list, int number) {
    if (isEmpty(list)) {
        return -1;
    }
    ListElement *element = list->head;
    int index = 0;
    while (element->next) {
        if (element->number == number) {
            return index;
        }
        element = element->next;
        ++index;
    }
    return -1;
}

int insertByOrder(List *list, int number, int path) {
    if (isEmpty(list)) {
        int errorCode = push(&list, number, path);
        if (errorCode != 0) {
            return 1;
        }
        return 0;
    }
    if (list->head->path >= path) {
        int errorCode = push(&list, number, path);
        if (errorCode != 0) {
            return 1;
        }
        return 0;
    }
    ListElement *element = list->head;
    ListElement *previous = list->head;
    while (element->path <= path && element->next) {
        previous = element;
        element = element->next;
    }
    if ((!element->next) && (element->path <= path)) {
        ListElement *newElement = (ListElement *)calloc(1, sizeof(ListElement));
        if (newElement == NULL) {
            return 1;
        }
        newElement->number = number;
        newElement->path = path;
        newElement->next = NULL;
        element->next = newElement;
        ++list->size;
        return 0;
    }
    ListElement *newElement = (ListElement *)calloc(1, sizeof(ListElement));
    if (newElement == NULL) {
        return 1;
    }
    newElement->number = number;
    newElement->path = path;
    if (previous->next) {
        newElement->next = previous->next;
    } else {
        newElement->next = NULL;
    }
    previous->next = newElement;
    ++list->size;
    return 0;
}

int push(List **list, int number, int path) {
    ListElement *newNode = (ListElement *)calloc(1, sizeof(ListElement));
    if (newNode == NULL) {
        return 1;
    }
    newNode->number = number;
    newNode->path = path;
    newNode->next = (*list)->head;
    (*list)->head = newNode;
    ++(*list)->size;
    return 0;
}

int pop(List **list, int *number, int *path) {
    if (isEmpty(*list)) {
        return 1;
    }
    ListElement *previous = (*list)->head;
    *number = previous->number;
    *path = previous->path;
    ((*list)->head) = ((*list)->head)->next;
    --(*list)->size;
    free(previous);
    return 0;
}

bool isEmpty(List *list) {
    if (list == NULL) {
        return true;
    }
    return list->head == NULL;
}

void printList(List *list) {
    if (isEmpty(list)) {
        printf("List is empty\n");
    }
    ListElement *element = list->head;
    while (element != NULL) {
        if (!element->next) {
            printf("%d%s", element->number, "\n");
        } else {
            printf("%d%s", element->number, ", ");
        }
        element = element->next;
    }
}