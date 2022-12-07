#include <stdio.h>
#include <stdlib.h>
#include "../List/list.h"
#include "../List/test.h"

typedef enum ErrorCode {
    fileNotFound,
    wrongInput,
    listError,
    ok
} ErrorCode;

ErrorCode reformatFileData(const char *path, List **list, int boundFirst, int boundSecond) {
    if (boundSecond < boundFirst) {
        return wrongInput;
    }
    FILE *fileInput = fopen(path, "r");
    if (fileInput == NULL) {
        return fileNotFound;
    }
    List *listAB = createList();
    List *listLow = createList();
    List *listUp = createList();
    char number[15] = {0};
    while (fscanf(fileInput, "%s", number) > 0) {
        int element = atoi(number);
        int error = 0;
        if (element >= boundFirst && element <= boundSecond) {
            error = pushBack(&listAB, element);
        } else if (element > boundSecond) {
            error = pushBack(&listUp, element);
        } else {
            error = pushBack(&listLow, element);
        }
        if (error == 1) {
            fclose(fileInput);
            deleteList(&listAB);
            deleteList(&listUp);
            deleteList(&listLow);
            return listError;
        }
    }
    fclose(fileInput);
    *list = makeOne(makeOne(listLow, listAB), listUp);
    int error = 0;
    error = deleteList(&listUp);
    if (error == 1) {
        deleteList(&listAB);
        deleteList(&listLow);
        return listError;
    }
    error = deleteList(&listAB);
    if (error == 1) {
        deleteList(&listUp);
        deleteList(&listLow);
        return listError;
    }
    error = deleteList(&listLow);
    if (error == 1) {
        deleteList(&listAB);
        deleteList(&listUp);
        return listError;
    }
    return ok;
}

bool test() {
    List *list = NULL;
    ErrorCode errorCode = reformatFileData("../testData", &list, -1, 5);
    if (errorCode != ok) {
        return false;
    }
    printList(list,"../testOutput");
    deleteList(&list);
    int correctSequence[10] = {-3, -2, -1, 5, 2, 3, 10, 8, 14, 6};
    int numbersRead = 0;
    char number[15] = {0};
    FILE *fileInput = fopen("../testOutput", "r");
    if (fileInput == NULL) {
        return false;
    }
    while (fscanf(fileInput, "%s", number) > 0) {
        if (numbersRead == 10) {
            ++numbersRead;
            break;
        }
        int element = atoi(number);
        if (element != correctSequence[numbersRead]) {
            break;
        }
        ++numbersRead;
    }
    fclose(fileInput);
    return numbersRead == 10;
}

int main() {
    if (!testIsEmpty() || !testPop() || !testCreate()) {
        printf("Some problems with list");
        return 1;
    }
    if (!test()) {
        printf("Test has been failed");
        return 1;
    }
    printf("enter a and b values (a <= b):\n");
    int boundFirst = 0;
    int boundSecond = 0;
    scanf("%d", &boundFirst);
    scanf("%d", &boundSecond);
    List *list = NULL;
    reformatFileData("../input", &list, boundFirst, boundSecond);
    printList(list, "../output");
    int error = deleteList(&list);
    if (error == 1) {
        printf("Problems with delete");
        return 1;
    }
    return 0;
}
