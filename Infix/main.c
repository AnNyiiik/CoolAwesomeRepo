#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../StackModule/stack.h"
#include "../StackModule/test.h"

int infixToPostfix(char const *sequence, char *sequencePostfix) {
    Node *head = NULL;
    size_t size = strlen(sequence);
    int index = 0;
    for (size_t i = 0; i < size; i++) {
        if (sequence[i] - '0' <= 9 && sequence[i] - '0' >= 0) {
            sequencePostfix[index] = sequence[i];
            ++index;
        } else {
            if (sequence[i] == '(') {
                int errorCode = pushBack(&head, (int)sequence[i]);
                if (errorCode != 0) {
                    printf("%s", "some problems with pushBack");
                    deleteAll(&head);
                    return 1;
                }
            } else if (sequence[i] == ')') {
                int returnValue = 0;
                int errorCode = pop(&head, &returnValue);
                if (errorCode != 0) {
                    printf("%s", "some problems with pop");
                    deleteAll(&head);
                    return 1;
                }
                while ((char)returnValue != '(') {
                    sequencePostfix[index] = (char)returnValue;
                    ++index;
                    errorCode = pop(&head, &returnValue);
                    if (errorCode != 0) {
                        printf("%s", "some problems with pop");
                        deleteAll(&head);
                        return 1;
                    }
                }
            } else if ((sequence[i] == '+') || (sequence[i] == '*') || (sequence[i] == '/') || (sequence[i] == '-')) {
                if (!isEmpty(head)) {
                    int returnValue = 0;
                    int errorCode = pop(&head, &returnValue);
                    if (errorCode != 0) {
                        printf("%s", "some problems with pop");
                        deleteAll(&head);
                        return 1;
                    }
                    if ((char) returnValue == '*' || (char) returnValue == '/') {
                        sequencePostfix[index] = (char) returnValue;
                        ++index;
                    } else if (((char) returnValue == '+' || (char) returnValue == '-') && (sequence[i] == '+' ||
                    sequence[i] == '-')) {
                        sequencePostfix[index] = (char) returnValue;
                        ++index;
                    } else {
                        errorCode = pushBack(&head, returnValue);
                        if (errorCode != 0) {
                            printf("%s", "some problems with pushBack");
                            deleteAll(&head);
                            return 1;
                        }
                    }
                    errorCode = pushBack(&head, (int) sequence[i]);
                    if (errorCode != 0) {
                        printf("%s", "some problems with pop");
                        deleteAll(&head);
                        return 1;
                    }
                } else {
                    int errorCode = pushBack(&head, (int) sequence[i]);
                    if (errorCode != 0) {
                        printf("%s", "some problems with pop");
                        deleteAll(&head);
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
            deleteAll(&head);
            return 1;
        }
        sequencePostfix[index] = (char) returnValue;
        ++index;
    }
    deleteAll(&head);
    return 0;
}

bool test(void) {
    char *testCases[4] = {"1+2-3*8", "1+2", "3*(1+2)", "(3+5)*4-9*2"};
    char *correctAnswers[4] = {"12+38*-", "12+", "312+*", "35+4*92*-"};
    for (int i = 0; i < 4; ++i) {
        char result[100] = {0};
        int errorCode = infixToPostfix(testCases[i], result);
        if (errorCode != 0) {
            return false;
        }
        int size = strlen(correctAnswers[i]);
        for (int j = 0; j < size; ++j) {
            if (result[j] != correctAnswers[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    if (!testPush()) {
        printf("%s", "some problems with push");
        return 1;
    }
    if (!testPop()) {
        printf("%s", "some problems with pop");
        return 1;
    }
    if (!testDeleteAll()) {
        printf("%s", "some problems with deleteAll");
        return 1;
    }
    if (!testIsEmpty()) {
        printf("%s", "some problems with isEmpty");
        return 1;
    }
    if (!test()) {
        printf("tests of infixToPostfix function are failed\n");
        return 1;
    }
    char sequence[100] = {0};
    printf("%s", "Enter the sequence:\n");
    scanf("%s", sequence);
    char sequencePostfix[100] = {0};
    int errorCode = infixToPostfix(sequence, sequencePostfix);
    if (errorCode != 0) {
        printf("%s", "problems with function infixToPostfix!!\n");
        return 1;
    }
    printf("%s", sequencePostfix);
    return 0;
}
//1+2-3*8
