#include <stdio.h>
#include "sort.h"
#include "test.h"
int main() {
    if (!testCreate() || !testDelete() || !testPushBack() || !testPop() || !testIsEmpty() || !testSort()) {
        return 1;
    }
    List *list = createList();
    FILE *file = fopen("../people&phones", "r");
    if (file == NULL) {
        printf("%s", "Файл не найден!");
        return 1;
    }
    while (!feof(file)) {
        char bufferName[100] = {0};
        char bufferNumber[30] = {0};
        const int readBytes = fscanf(file, "%s%s", bufferName, bufferNumber);
        if (readBytes < 0) {
            break;
        }
        pushBack(&list, bufferName, bufferNumber);
    }
    fclose(file);
    printf("Enter 0 to sort by name, 1 - by phone:\n");
    int option = 0;
    scanf("%d", &option);
    sort(&list, option);
    printList(list);
    deleteList(list);
    return 0;
}
