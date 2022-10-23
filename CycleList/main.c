#include <stdio.h>
#include "cycleList.h"
int main() {
    List *list = createList();
    pushBack(&list, 1);
    pushBack(&list, 2);
    pushBack(&list, 3);
    pushBack(&list, 4);
    delete(list, 2);
    deleteList(list);
}
