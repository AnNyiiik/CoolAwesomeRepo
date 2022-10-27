#include <stdio.h>
#include "list.h"
#include "test.h"
int main() {
    if (!testCreate()) {
        return 1;
    }
    if (!testDelete()) {
        return 1;
    }
    if (!testInsert()) {
        return 1;
    }
    if (!testPop()) {
        return 1;
    }
    if (!testIsEmpty()) {
        return 1;
    }
    if (!testInsertByOrder()) {
        return 1;
    }
    List *list = createList();
    push(&list, 12);
    push(&list, 13);
    push(&list, 16);
    insertByOrder(list, 17);
    deleteList(&list);
    return 0;
}
