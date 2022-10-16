#include <stdio.h>
#include "stack.h"
int main() {
    Node *head = NULL;
    pushBack(&head, "a");
    pushBack(&head, "b");
    pushBack(&head, "c");
    deleteAll(&head);
}
