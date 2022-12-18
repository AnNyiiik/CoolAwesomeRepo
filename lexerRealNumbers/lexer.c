#include "lexer.h"

void naturalNumberParse(char const *string, bool *isNotCorrect, int *index) {
    States state = waitingForFirstDigit;
    int length = strlen(string) - *index;
    int currentIndex = 0;
    while (true) {
        if (currentIndex == length) {
            *isNotCorrect = (currentIndex == 0);
            *index = *index + currentIndex;
            return;
        } else {
            char character = string[currentIndex + *index];
            if (isdigit(character) && state == waitingForFirstDigit) {
                state = waitingForOtherDigit;
                ++(currentIndex);
            } else if (isdigit(character) && state == waitingForOtherDigit) {
                ++(currentIndex);
            } else {
                *isNotCorrect = (currentIndex == 0);
                *index = *index + currentIndex;
                return;
            }
        }
    }
}

bool isRealNumber(const char *string) {
    States  state = integerPartDone;
    bool isNotCorrect = false;
    int index = 0;
    naturalNumberParse(string, &isNotCorrect, &index);
    int length = strlen(string);
    while (true) {
        if (isNotCorrect) {
            return false;
        }
        if (index == length) {
            return state != expDone;
        }
        char character = string[index];
        if (character == '.' && state == integerPartDone) {
            ++index;
            naturalNumberParse(string, &isNotCorrect, &index);
            state = fractionPartDone;
        } else if (character == 'E' && (state == integerPartDone || state == fractionPartDone)) {
            state = expDone;
            ++index;
        } else if (state == expDone) {
            state = powerDone;
            if (character == '+' || character == '-') {
                ++index;
                naturalNumberParse(string, &isNotCorrect, &index);
            } else {
                naturalNumberParse(string, &isNotCorrect, &index);
            }
        } else {
            return false;
        }
    }
}