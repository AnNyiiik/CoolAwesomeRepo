#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "test.h"

bool testPush(void) {
    Node *head = NULL;
    int errorCode = pushBack(&head, 3);
    if (errorCode != 0) {
        free(head);
        return false;
    }
    if (head->value == 3) {
        free(head);
        return true;
    }
    free(head);
    return false;
}

bool testPop(void) {
    Node *head = NULL;
    int errorCode = pushBack(&head, 3);
    if (errorCode != 0) {
        free(head);
        return false;
    }
    int value = 0;
    errorCode = pop(&head, &value);
    if (errorCode != 0) {
        free(head);
        return false;
    }

    free(head);
    return value == 3;
}

bool testDeleteAll(void) {
    Node *head = NULL;
    for (int i = 0; i < 10; ++i) {
        int errorCode = pushBack(&head, 3);
        if (errorCode != 0) {
            free(head);
            return false;
        }
    }
    int errorCode = deleteAll(&head);
    if (errorCode != 0) {
        return false;
    }
    return head == NULL;
}

bool testIsEmpty(void) {
    Node *head = NULL;
    return isEmpty(head);
}