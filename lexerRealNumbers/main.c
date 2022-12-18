#include <stdio.h>
#include "test.h"
#include "lexer.h"

int main() {
    if (!testFalse() || !testFalse()) {
        return 1;
    }
    printf("Enter the string\n");
    char string[30] = {0};
    scanf("%s", string);
    if (isRealNumber(string)) {
        printf("It's a correct number");
    } else {
        printf("It's not a correct number");
    }
    return 0;
}
