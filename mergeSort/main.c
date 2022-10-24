#include <stdio.h>
#include "sort.h"
#include "test.h"
int main() {
    if (!testCreate()) {
        return 1;
    }
    if (!testDelete()) {
        return 1;
    }
    if (!testPushBack()) {
        return 1;
    }
    if (!testPop()) {
        return 1;
    }
    
    List *list = createList();
    pushBack(&list, "W", "7896");
    pushBack(&list, "B", "8906");
    pushBack(&list, "G", "9018");
    sort(&list, 0);
    printList(list);
    deleteList(list);
}
