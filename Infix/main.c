#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../StackModule/stack.h"
int main() {
    Node *head = NULL;
    char *sequence = (char*) malloc(sizeof(char) * 100);
    printf("%s", "Enter the sequence:\n");
    scanf("%s", sequence);
    int size = strlen(sequence);
    char *sequencePostfix = (char*) malloc(sizeof(char) * 100);
    int index = 0;
    for (int i = 0; i < size; i++) {
        int errorCode = 0;
        int returnValue = 0;
        if (((int) sequence[i] - 48 <= 9) && ((int) sequence[i] - 48 >= 0)) {
            sequencePostfix[index] = sequence[i];
            ++index;
        } else {
            if (sequence[i] == '(') {
                errorCode = pushBack(&head, (int) sequence[i]);
                if (errorCode != 0) {
                    printf("%s", "some problems with pushBack");
                    return 1;
                }
            } else if (sequence[i] == ')') {
                errorCode = pop(&head, &returnValue);
                if (errorCode != 0) {
                    printf("%s", "some problems with pop");
                    return 1;
                }
                while ((char) returnValue != '(') {
                    sequencePostfix[index] = (char) returnValue;
                    ++index;
                    errorCode = pop(&head, &returnValue);
                    if (errorCode != 0) {
                        printf("%s", "some problems with pop");
                        return 1;
                    }
                }
            } else if ((sequence[i] == '+') || (sequence[i] == '*') || (sequence[i] == '/') || (sequence[i] == '-')) {
                if (!isEmpty(head)) {
                    errorCode = pop(&head, &returnValue);
                    if (errorCode != 0) {
                        printf("%s", "some problems with pop");
                        return 1;
                    }
                    if ((char) returnValue == '*' || (char) returnValue == '/') {
                        sequencePostfix[index] = (char) returnValue;
                    } else {
                        errorCode = pushBack(&head, returnValue);
                        if (errorCode != 0) {
                            printf("%s", "some problems with pushBack");
                            return 1;
                        }
                    }
                    errorCode = pushBack(&head, (int) sequence[i]);
                    if (errorCode != 0) {
                        printf("%s", "some problems with pop");
                        return 1;
                    }
                } else {
                    errorCode = pushBack(&head, (int) sequence[i]);
                    if (errorCode != 0) {
                        printf("%s", "some problems with pop");
                        return 1;
                    }
                }
            }
        }
    }
    while (!isEmpty(head)) {
        int returnValue = 0;
        int errorCode = pop(&head, &returnValue);
        if (errorCode != 0) {
            printf("%s", "some problems with pop");
            return 1;
        }
        sequencePostfix[index] = (char) returnValue;
        ++index;
    }
    deleteAll(&head);
    free(sequence);
    printf("%s", sequencePostfix);
    free(sequencePostfix);
}
