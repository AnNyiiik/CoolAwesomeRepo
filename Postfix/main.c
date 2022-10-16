#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../StackModule/stack.h"

int main() {
    Node *head = NULL;
    printf("Enter the expression:\n");
    char *postfixExpression = (char*) malloc(sizeof(char) * 100);
    scanf("%s", postfixExpression);
    int size = strlen(postfixExpression);
    for (int i = 0; i < size; ++i) {
        if ((int) postfixExpression[i] < 10 && (int) postfixExpression[i] >= 0) {
            pushBack(&head, postfixExpression[i]);
        } else {
            int temporaryValue = 0;
            int returnValue = 0;
            int errorCode = 0;
            if (postfixExpression[i] == '+') {
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
                int sign = 1;
                for (int i = 0; i < 2; ++i) {
                    errorCode = pop(&head, &returnValue);
                    if (errorCode != 0) {
                        return 1;
                    }
                    temporaryValue = temporaryValue + returnValue * sign;
                    sign = -1;
                }
                errorCode = pushBack(&head, temporaryValue);
                if (errorCode != 0) {
                    return 1;
                }
            } else if (postfixExpression[i] == '*') {

            }
        }
    }
}
