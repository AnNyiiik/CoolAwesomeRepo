#ifndef LEXERREALNUMBERS_LEXER_H
#define LEXERREALNUMBERS_LEXER_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum States {
    waitingStart = 0,
    integerPartInProcess = 1,
    startFraction = 2,
    fractionPartInProcess = 3,
    startExponent = 4,
    powerPartInProcess = 5,
} States;

bool isRealNumber(const char *string);

#endif //LEXERREALNUMBERS_LEXER_H
