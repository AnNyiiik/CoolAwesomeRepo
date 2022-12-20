#include "lexer.h"

bool isRealNumber(const char *string) {
    int position = -1;
    int length = strlen(string);
    States state = waitingStart;
    while (position < length - 1) {
        ++position;
        switch (state) {
            case waitingStart:
                if (isdigit(string[position])) {
                    state = integerPartInProcess;
                } else {
                    return false;
                }
                break;
            case integerPartInProcess:
                if (string[position] == 'E') {
                    state = startExponent;
                } else if (string[position] == '.') {
                    state = startFraction;
                } else if (!isdigit(string[position])) {
                    return false;
                }
                break;
            case startFraction:
                if (!isdigit(string[position])) {
                    return false;
                }
                state = fractionPartInProcess;
                break;
            case fractionPartInProcess:
                if (string[position] == 'E') {
                    state = startExponent;
                } else if (!isdigit(string[position])) {
                    return false;
                }
                break;
            case startExponent:
                if (string[position] == '+' || string[position] == '-') {
                    state = startExponentSign;
                } else if (!isdigit(string[position])) {
                    return false;
                } else {
                    state = powerPartInProcess;
                }
                break;
            case startExponentSign:
                if (!isdigit(string[position])) {
                    return false;
                }
                state = powerPartInProcess;
                break;
            case powerPartInProcess:
                if (!isdigit(string[position])) {
                    return false;
                }
                break;
        }
    }
    return state == powerPartInProcess || state == fractionPartInProcess || state == integerPartInProcess;
}