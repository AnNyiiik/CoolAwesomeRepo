#include <stdio.h>
#include "cycleList.h"
#include "test.h"
int main() {
    if (!testCreate()) {
        return 1;
    }
    if (!testPushBack()) {
        return 1;
    }
    if (!testPop()) {
        return 1;
    }
    if (!testDelete()) {
        return 1;
    }
    if (!testIsEmpty()) {
        return 1;
    }
    List *list = createList();
    pushBack(&list, 1);
    pushBack(&list, 2);
    pushBack(&list, 3);
    pushBack(&list, 4);
    delete(list, 2);
    deleteList(list);
}
