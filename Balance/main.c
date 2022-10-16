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
    bool answer = true;
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
            if (isEmpty(&head)) {
                answer = false;
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
            answer = false;
            break;
        }
    }
    free(sequence);
    if (!isEmpty(&head)) {
        answer = false;
    }
    deleteAll(&head);
    if (answer) {
        printf("%s", "The sequence is correct");
    } else {
        printf("%s", "The sequence is incorrect");
    }
    return 0;
}
