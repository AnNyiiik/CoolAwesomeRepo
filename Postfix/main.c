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
            pushBack(&head, (int) postfixExpression);
        }
    }
}
