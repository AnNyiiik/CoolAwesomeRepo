#include <stdio.h>
#include <stdlib.h>
#include "../List/list.h"
#include "../List/test.h"

int main() {
    if (!testIsEmpty() || !testPop() || !testCreate() || !testDelete() || !testInsertByOrder() || !testInsert()) {
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
    FILE *fileInput = fopen("../input.txt", "r");
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
            push(&listAB, element);
        } else if (element > boundSecond) {
            push(&listUp, element);
        } else {
            push(&listLow, element);
        }
    }
    return 0;
}
