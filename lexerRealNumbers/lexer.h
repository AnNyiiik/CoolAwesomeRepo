#ifndef LEXERREALNUMBERS_LEXER_H
#define LEXERREALNUMBERS_LEXER_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

// States of DFA.
typedef enum States {
    waitingStart,
    integerPartInProcess,
    startFraction,
    fractionPartInProcess,
    startExponent,
    powerPartInProcess,
} States;

// Check if the given string representation of a number is a correct real number.
bool isRealNumber(const char *string);

#endif //LEXERREALNUMBERS_LEXER_H
