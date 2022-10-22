#include <stdio.h>
#include "list.h"
int main() {
    List *list = createList();
    push(&list, 12);
    push(&list, 13);
    int value = 0;
    pop(&list, &value);
    deleteList(&list);
    return 0;
}
