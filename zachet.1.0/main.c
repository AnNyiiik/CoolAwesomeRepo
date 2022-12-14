#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../List/list.h"
#include "../List/test.h"

#define BINARY_SIZE 32

int convertToDecimal(const char *binaryString, char *result) {
    if (strlen(binaryString) > BINARY_SIZE) {
        return 1;
    } else if (strlen(binaryString) == 0) {
        return 1;
    }
    int base = 1;
    int decimal = 0;
    int length = strlen(binaryString);
    for (int i = length - 1; i >= 0; --i) {
        decimal += base * (binaryString[i] - '0');
        base = base * 2;
    }
    sprintf(result, "%d", decimal);
    return 0;
}

bool testConversion(void) {
    char *result = (char*)calloc(BINARY_SIZE,sizeof(char));
    if (result == NULL) {
        return false;
    }
    convertToDecimal("101", result);
    if (strcmp(result, "5") != 0) {
        free(result);
        return false;
    }
    convertToDecimal("1010", result);
    if (strcmp(result, "10") != 0) {
        free(result);
        return false;
    }
    free(result);
    return true;
}

int main() {
    if (!testConversion()) {
        return 1;
    }
    char *result = (char *)calloc(BINARY_SIZE, sizeof(char));
    if (result == NULL) {
        return 1;
    }
    int error = convertToDecimal("101010", result);
    if (error == 1) {
        printf("Invalid data");
        free(result);
        return 1;
    }
    printf("The result is %s\n", result);
    free(result);
    if (!testAddA() || !testPushBack() || !testIsEmpty() || !testPop() || !testDelete() || !testCreate()) {
        return 1;
    }
    error = 0;
    List *list = createList(&error);
    if (error == 1) {
        return false;
    }
    pushBack(&list, "a");
    pushBack(&list, "b");
    pushBack(&list, "c");
    addStringsStartsWithA(&list);
    return 0;
}
