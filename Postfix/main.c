#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../StackModule/stack.h"
#include "../StackModule/test.h"

int main() {
    if (!testPush()) {
        printf("%s", "Problems with push!");
        return 1;
    }
    if (!testPop()) {
        printf("%s", "Problems with pop!");
        return 1;
    }
    if (!testDeleteAll()) {
        printf("%s", "Problems with deleteAll!");
        return 1;
    }
    if (!testIsEmpty()) {
        printf("%s", "Problems with isEmpty!");
        return 1;
    }
    Node *head = NULL;
    printf("Enter the expression:\n");
    char *postfixExpression = (char*) malloc(sizeof(char) * 100);
    scanf("%s", postfixExpression);
    int size = strlen(postfixExpression);
    int temporaryValue = 0;
    for (int i = 0; i < size; ++i) {
        if (((int) postfixExpression[i] - 48 < 10) && ((int) postfixExpression[i] - 48 >= 0)) {
            pushBack(&head, (int) postfixExpression[i] - 48);
        } else {
            int returnValue = 0;
            int errorCode = 0;
            if (postfixExpression[i] == '+') {
                temporaryValue = 0;
                for (int i = 0; i < 2; ++i) {
                    errorCode = pop(&head, &returnValue);
                    if (errorCode != 0) {
                        return 1;
                    }
                    temporaryValue = temporaryValue + returnValue;
                }
                errorCode = pushBack(&head, temporaryValue);
                if (errorCode != 0) {
                    return 1;
                }
            } else if (postfixExpression[i] == '-') {
                int sign = -1;
                temporaryValue = 0;
                for (int i = 0; i < 2; ++i) {
                    errorCode = pop(&head, &returnValue);
                    if (errorCode != 0) {
                        return 1;
                    }
                    temporaryValue = temporaryValue + returnValue * sign;
                    sign = 1;
                }
                errorCode = pushBack(&head, temporaryValue);
                if (errorCode != 0) {
                    return 1;
                }
            } else if (postfixExpression[i] == '*') {
                temporaryValue = 1;
                for (int i = 0; i < 2; ++i) {
                    errorCode = pop(&head, &returnValue);
                    if (errorCode != 0) {
                        return 1;
                    }
                    temporaryValue = temporaryValue * returnValue;
                }
                errorCode = pushBack(&head, temporaryValue);
                if (errorCode != 0) {
                    return 1;
                }
            } else if (postfixExpression[i] == '/') {
                temporaryValue = 1;
                for (int i = 0; i < 2; ++i) {
                    errorCode = pop(&head, &returnValue);
                    if (errorCode != 0) {
                        return 1;
                    }
                    temporaryValue = (i == 0) ? (temporaryValue * returnValue) : (temporaryValue / returnValue);
                }
                errorCode = pushBack(&head, temporaryValue);
                if (errorCode != 0) {
                    return 1;
                }
            }
        }
    }
    printf("%d", temporaryValue);
    free(postfixExpression);
}
