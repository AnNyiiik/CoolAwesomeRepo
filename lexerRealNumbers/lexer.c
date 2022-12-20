#include "lexer.h"

bool isRealNumber(const char *string) {
    int position = 0;
    int length = strlen(string);
    States state = waitingStart;
    States newState = waitingStart;
    while (position < length) {
        switch (state) {
            case waitingStart:
                if (!isdigit(string[position])) {
                    return false;
                }
                newState = integerPartInProcess;
                ++position;
                break;
            case integerPartInProcess:
                if (string[position] == 'E') {
                    ++position;
                    newState = startExponent;
                } else if (string[position] == '.') {
                    newState = startFraction;
                } else if (!isdigit(string[position])){
                    return false;
                }
                ++position;
                break;
            case startFraction:
                if (!isdigit(string[position])) {
                    return false;
                }
                ++position;
                newState = fractionPartInProcess;
                break;
            case fractionPartInProcess:
                if (string[position] == 'E') {
                    ++position;
                    newState = startExponent;
                } else if (!isdigit(string[position])) {
                    return false;
                }
                ++position;
                break;
            case startExponent:
                if (string[position] == '+' || string[position] == '-') {
                    ++position;
                } else if (!isdigit(string[position])) {
                    return false;
                } else {
                    newState = powerPartInProcess;
                    ++position;
                }
                break;
            case powerPartInProcess:
                if (!isdigit(string[position])) {
                    return false;
                }
                ++position;
                break;
        }
        state = newState;
    }
    return state == powerPartInProcess || state == fractionPartInProcess || state == integerPartInProcess;
}