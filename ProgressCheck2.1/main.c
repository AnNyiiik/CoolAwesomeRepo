#include <stdio.h>
#include <stdlib.h>
#include "../List/list.h"
#include "../List/test.h"

int main() {
    if (!testIsEmpty() || !testPop() || !testCreate()) {
        return 1;
    }
    printf("enter a and b values (a > b):\n");
    int boundFirst = 0;
    int boundSecond = 0;
    scanf("%d", &boundFirst);
    scanf("%d", &boundSecond);
    if (boundFirst > boundSecond) {
        return 1;
    }
    FILE *fileInput = fopen("../input", "r");
    if (fileInput == NULL) {
        return 1;
    }
    List *listAB = createList();
    List *listLow = createList();
    List *listUp = createList();
    char number[15] = {0};
    while (fscanf(fileInput, "%s", number) > 0) {
        int element = atoi(number);
        if (element >= boundFirst && element <= boundSecond) {
            pushBack(&listAB, element);
        } else if (element > boundSecond) {
            pushBack(&listUp, element);
        } else {
            pushBack(&listLow, element);
        }
    }
    fclose(fileInput);
    List *list = makeOne(makeOne(listLow, listAB), listUp);
    printList(list, "../output");
    deleteList(&listUp);
    deleteList(&listAB);
    deleteList(&listLow);
    deleteList(&list);
    return 0;
}
