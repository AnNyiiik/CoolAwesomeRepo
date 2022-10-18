#include <stdio.h>
#include "stack.h"
#include "test.h"
int main() {
    if (!testPush()) {
        return 1;
    }
    if (!testPop()) {
        return 1;
    }
    if (!testDeleteAll()) {
        return 1;
    }
    if (!testIsEmpty()) {
        return 1;
    }
    Node *head = NULL;
    pushBack(&head, "a");
    pushBack(&head, "b");
    pushBack(&head, "c");
    deleteAll(&head);
    return 0;
}
