#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

int pushBack(Node **Last, int value) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        return 1;
    }
    newNode->value = value;
    newNode->next = (*Last);
    (*Last) = newNode;
    return 0;
}

int pop(Node **head, int *value) {
    if (head == NULL) {
        return 1;
    }
    Node *previous = (*head);
    *value = (*head)->value;
    (*head) = (*head)->next;
    free(previous);
    return 0;
}

bool isEmpty(Node *head) {
    return head == NULL;
}

int deleteAll(Node **head) {
    while (!isEmpty(*head)) {
        int value = 0;
        int errorCode = pop(head, &value);
        if (errorCode != 0) {
            return errorCode;
        }
    }
    return 0;
}


