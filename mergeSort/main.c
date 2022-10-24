#include <stdio.h>
#include "sort.h"
int main() {
    List *list = createList();
    pushBack(&list, "W", "7896");
    pushBack(&list, "B", "8906");
    pushBack(&list, "G", "9018");
    sort(&list, 0);
    printList(list);
    deleteList(list);
}
