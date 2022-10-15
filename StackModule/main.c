#include <stdio.h>
#include "stack.h"
int main() {
    Node *head = NULL;
    pushBack(&head, 1);
    pushBack(&head, 2);
    pushBack(&head, 3);
    deleteAll(&head);
}
