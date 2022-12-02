#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../StackModule/stack.h"
#include "../StackModule/test.h"

int checkBalance(char *sequence, bool *result) {
    Node *head = NULL;
    *result = true;
    int size = strlen(sequence);
    for (int i = 0; i < size; ++i) {
        int errorCode = 0;
        int returnValue = 0;
        if ((sequence[i] == '(') || (sequence[i] == '{') || (sequence[i] == '[')) {
            errorCode = pushBack(&head, (int)sequence[i]);
            if (errorCode != 0) {
                printf("%s", "was an error during push");
                return 1;
            }
        } else if ((sequence[i] == ')') || (sequence[i] == '}') || (sequence[i] == ']')) {
            if (isEmpty(head)) {
                *result = false;
                break;
            }
            errorCode = pop(&head, &returnValue);
            if (errorCode != 0) {
                printf("%s", "was an error during pop");
                return 1;
            }
            if (((int) sequence[i] == returnValue + 1) || ((int) sequence[i] == returnValue + 2)) {
                continue;
            }
            *result = false;
            break;
        }
    }
    if (!isEmpty(head)) {
        *result = false;
    }
    deleteAll(&head);
    return 0;
}

bool test(void) {
    char *samples[3] = {"{{}[(()())]}", "[[)]", "]][["};
    bool result = false;
    for (int i = 0; i < 3; ++i) {
        int errorCode = checkBalance(samples[i], &result);
        if (errorCode != 0) {
            return false;
        }
        if (i == 0) {
            if (!result){
                return false;
            }
        } else if (i == 1) {
            if (result) {
                return false;
            }
        } else {
            return (!result);
        }
    }
}

int main() {
    if (!test()) {
        printf("%s", "The algorithm is incorrect!");
        return 1;
    }
    char sequence[100] = {0};
    printf("%s", "Enter the sequence:\n");
    scanf("%s", sequence);
    bool result = true;
    int errorCode = checkBalance(sequence, &result);
    if (errorCode != 0) {
        return 1;
    }
    if (result) {
        printf("%s", "The sequence is correct.");
    } else {
        printf("%s", "The sequence is incorrect.");
    }
}
