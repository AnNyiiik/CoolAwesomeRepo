#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../StackModule/stack.h"
#include "../StackModule/test.h"

int postfixCalculation(char const *postfixExpression, int *result) {
    Node *head = NULL;
    int size = strlen(postfixExpression);
    int temporaryValue = 0;
    for (int i = 0; i < size; ++i) {
        if ((postfixExpression[i] - '0' < 10) && (postfixExpression[i] - '0' >= 0)) {
            pushBack(&head, postfixExpression[i] - '0');
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
                    if (i == 0 && returnValue == 0) {
                        return 1;
                    }
                    temporaryValue = (i == 0) ? returnValue : (temporaryValue / returnValue);
                }
                errorCode = pushBack(&head, temporaryValue);
                if (errorCode != 0) {
                    return 1;
                }
            }
        }
    }
    pop(&head, result);
    return isEmpty(head);
}

bool test(void) {
    char sampleTwo[7] = "45+23*-";
    char sampleThree[7] = "46*99/-";
    for (int i = 0; i < 3; ++i) {
        int result = 0;
        int errorCode = 0;
        if (i == 0) {
            errorCode = postfixCalculation("96-12+*", &result);
        } else if (i == 1) {
            errorCode = postfixCalculation(sampleTwo, &result);
        } else {
            errorCode = postfixCalculation(sampleThree, &result);
        }
        if (errorCode != 0) {
            return false;
        }
        if (i == 0 && result != 9) {
            return false;
        } else if (i == 1 && (result != 3)) {
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
    char postfixExpression[100] = {0};
    scanf("%s", postfixExpression);
    int result = 0;
    int errorCode = postfixCalculation(postfixExpression, &result);
    if (errorCode != 0) {
        return 1;
    }
    printf("%s%d", "The result is ", result);
    return 0;
}
