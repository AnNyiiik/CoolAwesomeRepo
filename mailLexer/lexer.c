#include "lexer.h"
#include <string.h>
#include <ctype.h>

typedef enum States {
    waitingForFirstCharacter,
    startAddress,
    addSign,
    waitingForPoint,
    Point,
    endCharacter
} States;

bool isCorrectMail(char const *string) {
    if (string == NULL) {
        return false;
    }
    int size = strlen(string);
    States state = waitingForFirstCharacter;
    int position = -1;
    while (position < size - 1) {
        ++position;
        switch (state) {
            case waitingForFirstCharacter:
                if (string[position] >= 65 && string[position] <= 90 || isdigit(string[position])
                || string[position] == '.' || string[position] == '_' || string[position] == '%'
                || string[position] == '+' || string[position] == '-') {
                    state = startAddress;
                } else {
                    return false;
                }
                break;
            case startAddress:
                if (string[position] == '@') {
                    state = addSign;
                } else if (!(string[position] >= 65 && string[position] <= 90 || isdigit(string[position])
                           || string[position] == '.' || string[position] == '_' || string[position] == '%'
                           || string[position] == '+' || string[position] == '-')) {
                    return false;
                }
                break;
            case addSign:
                if (string[position] >= 65 && string[position] <= 90 || isdigit(string[position])
                    || (string[position] == '-')) {
                    state = waitingForPoint;
                } else {
                    return false;
                }
                break;
            case waitingForPoint:
                if (string[position] == '.') {
                    state = Point;
                } else if (!(string[position] >= 65 && string[position] <= 90
                    || isdigit(string[position]) || string[position] == '-')) {
                    return false;
                }
                break;
            case Point:
                if (string[position] >= 65 && string[position] <= 90) {
                    state = endCharacter;
                } else if (string[position] >= 65 && string[position] <= 90
                           || isdigit(string[position]) || string[position] == '-') {
                    state = waitingForPoint;
                } else {
                    return false;
                }
                break;
            case endCharacter:
                if (string[position] >= 65 && string[position] <= 90
                    || isdigit(string[position]) || string[position] == '-') {
                    state = waitingForPoint;
                } else if (string[position] == '.') {
                    state = Point;
                } else {
                    return false;
                }
                break;
        }
    }
    return state == endCharacter;
}