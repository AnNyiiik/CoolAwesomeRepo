#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../List/list.h"
#include "../List/test.h"

int convertToDecimal(const char *binaryString, int *result) {
    if (strlen(binaryString) > 32) {
        return 1;
    } else if (strlen(binaryString) == 32 && binaryString[0] == '1') {
        return 1;
    } else if (strlen(binaryString) == 0) {
        return 1;
    }
    int base = 1;
    *result = 0;
    int length = strlen(binaryString);
    for (int i = length - 1; i >= 0; --i) {
        *result += base * (binaryString[i] - '0');
        base = base * 2;
    }
    return 0;
}

bool testConversion(void) {
    int result = 0;
    convertToDecimal("101", &result);
    if (result != 5) {
        return false;
    }
    convertToDecimal("1010", &result);
    if (result != 10) {
        return false;
    }
    return true;
}

int main() {
//    if (!testConversion()) {
//        return 1;
//    }
//    int result = 0;
//    convertToDecimal("101010", &result);
//    printf("The result is %d\n", result);
    if (!testAddA()) {
        return 1;
    }
    List *list = createList();
    pushBack(&list, "a");
    pushBack(&list, "b");
    pushBack(&list, "c");
    addStringsStartsWithA(&list);
    return 0;
}
