#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../StackModule/stack.h"
#include "../StackModule/test.h"

int postfixCaculation(char *postfixExpression, int *result) {
    Node *head = NULL;
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
    *result = temporaryValue;
    return 0;
}

bool test(void) {
    char sampleOne[7] = "96-12+*";
    char sampleTwo[7] = "45+23*-";
    char sampleThree[7] = "46*99/-";
    for (int i = 0; i < 3; ++i) {
        int result = 0;
        int errorCode = 0;
        if (i == 0) {
            errorCode = postfixCaculation(sampleOne, &result);
        } else if (i == 1) {
            errorCode = postfixCaculation(sampleTwo, &result);
        } else {
            errorCode = postfixCaculation(sampleThree, &result);
        }
        if (errorCode != 0) {
            return false;
        }
        if ((i == 0) && (result != 9)) {
            return false;
        } else if ((i == 1) && (result != 3)) {
            return false;
        } if (i == 2) {
            return (result == 23);
        }
    }
}

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
    if (!test()) {
        printf("%s", "Problems with algorithm!");
        return 1;
    }
    printf("Enter the expression:\n");
    char *postfixExpression = (char*) malloc(sizeof(char) * 100);
    scanf("%s", postfixExpression);
    int result = 0;
    int errorCode = postfixCaculation(postfixExpression, &result);
    if (errorCode != 0) {
        free(postfixExpression);
        return 1;
    }
    free(postfixExpression);
    printf("%s%d", "The result is ", result);
    return 0;
}
