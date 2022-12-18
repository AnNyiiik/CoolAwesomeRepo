#ifndef LEXERREALNUMBERS_LEXER_H
#define LEXERREALNUMBERS_LEXER_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum States {
    integerPartDone = 1,
    waitingForFirstDigit = 2,
    waitingForOtherDigit = 3,
    fractionPartDone = 4,
    powerDone = 5,
    expDone = 6
} States;

void naturalNumberParse(char const *string, bool *isNotCorrect, int *index);

bool isRealNumber(const char *string);

#endif //LEXERREALNUMBERS_LEXER_H
