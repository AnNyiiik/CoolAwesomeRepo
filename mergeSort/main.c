#include <stdio.h>
#include <stdlib.h>
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
    if (!testIsEmpty()) {
        return 1;
    }
    if (!testSort()) {
        return 1;
    }
    List *list = createList();
    FILE *file = fopen("/Users/annnikolaeff/CoolAwesomeRepo/mergeSort/people&phones", "r");
    if (file == NULL) {
        printf("%s", "Файл не найден!");
        return 1;
    }
    while (!feof(file)) {
        char *bufferName = malloc(sizeof(char) * 100);
        char *bufferNumber = malloc(sizeof(char) * 30);
        const int readBytes = fscanf(file, "%s%s", bufferName, bufferNumber);
        if (readBytes < 0) {
            free(bufferName);
            free(bufferNumber);
            break;
        }
        pushBack(&list, bufferName, bufferNumber);
        free(bufferName);
        free(bufferNumber);
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
