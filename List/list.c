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
    int size;
} List;

List *createList(void) {
    return calloc(1, sizeof(List));
}

int deleteList(List **list) {
    while (!isEmpty(*list)) {
        int value = 0;
        int errorCode = pop(list, &value);
        if (errorCode != 0) {
            return 1;
        }
    }
    free(*list);
    *list = NULL;
    return 0;
}

int insert(List *list, int place, int value) {
    if (isEmpty(list)) {
        int errorCode = push(&list, value);
        if (errorCode != 0) {
            return 1;
        }
        return 0;
    }
    if (place > list->size) {
        return 1;
    }
    if (place == 0) {
        int errorCode = push(&list, value);
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
    ListElement *newElement = (ListElement *) malloc(sizeof(ListElement));
    newElement->value = value;
    if (element->next) {
        newElement->next = element->next;
    } else {
        newElement->next = NULL;
    }
    element->next = newElement;
    ++list->size;
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
        int errorCode = pop(&list, &value);
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
        ListElement *elementAfterDeleted = element->next->next;
        free(element->next);
        element->next = elementAfterDeleted;
        --list->size;
        return 0;
    }
    --list->size;
    return 0;
}

int getElementPlace(List *list, int value) {
    if (isEmpty(list)) {
        return -1;
    }
    ListElement *element = list->head;
    int index = 0;
    while (element->next) {
        if (element->value == value) {
            return index;
        }
        element = element->next;
        ++index;
    }
    return -1;
}

int insertByOrder(List *list, int value) {
    if (isEmpty(list)) {
        int errorCode = push(&list, value);
        if (errorCode != 0) {
            return 1;
        }
        return 0;
    }
    if (list->head->value >= value) {
        int errorCode = push(&list, value);
        if (errorCode != 0) {
            return 1;
        }
        return 0;
    }
    ListElement *element = list->head;
    ListElement *previous = list->head;
    while (element->value <= value && element->next) {
        previous = element;
        element = element->next;
    }
    if (!element->next && element->value <= value) {
        ListElement *newElement = (ListElement *)calloc(1, sizeof(ListElement));
        newElement->value = value;
        element->next = newElement;
        ++list->size;
        return 0;
    }
    ListElement *newElement = (ListElement *)malloc(sizeof(ListElement));
    newElement->value = value;
    if (previous->next) {
        newElement->next = previous->next;
    } else {
        newElement->next = NULL;
    }
    previous->next = newElement;
    ++list->size;
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

bool isEmpty(List *list) {
    return list->head == NULL;
}

void printList(List *list) {
    if (isEmpty(list)) {
        printf("List is empty\n");
    }
    ListElement *element = list->head;
    while (element != NULL) {
        if (!element->next) {
            printf("%d%s", element->value, "\n");
        } else {
            printf("%d%s", element->value, ", ");
        }
        element = element->next;
    }
}

