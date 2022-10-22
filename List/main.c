#include <stdio.h>
#include "list.h"
int main() {
    List *list = createList();
    push(&list, 12);
    push(&list, 13);
    push(&list, 16);
    insert(list, 0, 14);
    delete(list, 2);
    deleteList(&list);
    return 0;
}
