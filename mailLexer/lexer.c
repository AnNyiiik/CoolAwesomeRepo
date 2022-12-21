#include "lexer.h"
#include <string.h>
#include <ctype.h>

typedef enum States {
    waitingForFirstCharacter,
    startAddress,
    addSign,
    waitingForPoint,
    point,
    endCharacter
} States;

bool conditionFirst(char character) {
    return character >= 65 && character <= 90 || isdigit(character)
           || character == '.' || character == '_' || character == '%'
           || character == '+' || character == '-';
}

bool conditionSecond(char character) {
    return character >= 65 && character <= 90 || isdigit(character)
           || character == '-';
}

bool conditionThird(char character) {
    return character >= 65 && character <= 90;
}

bool isCorrectMail(char const *string) {
    if (string == NULL) {
        return false;
    }
    int size = strlen(string);
    States state = waitingForFirstCharacter;
    int position = -1;
    while (position < size - 1) {
        ++position;
        char characterCurrent = string[position];
        switch (state) {
            case waitingForFirstCharacter:
                if (conditionFirst(characterCurrent)) {
                    state = startAddress;
                } else {
                    return false;
                }
                break;
            case startAddress:
                if (characterCurrent == '@') {
                    state = addSign;
                } else if (!conditionFirst(characterCurrent)) {
                    return false;
                }
                break;
            case addSign:
                if (conditionSecond(characterCurrent)) {
                    state = waitingForPoint;
                } else {
                    return false;
                }
                break;
            case waitingForPoint:
                if (characterCurrent == '.') {
                    state = point;
                } else if (!conditionSecond(characterCurrent)) {
                    return false;
                }
                break;
            case point:
                if (conditionThird(characterCurrent)) {
                    state = endCharacter;
                } else if (conditionSecond(characterCurrent)) {
                    state = waitingForPoint;
                } else {
                    return false;
                }
                break;
            case endCharacter:
                if (conditionSecond(characterCurrent)) {
                    state = waitingForPoint;
                } else if (characterCurrent == '.') {
                    state = point;
                } else {
                    return false;
                }
                break;
        }
    }
    return state == endCharacter;
}