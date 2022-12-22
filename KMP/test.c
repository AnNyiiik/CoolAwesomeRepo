#include "test.h"

bool test(void) {
    char *samplePatterns[3] = {"aba", "aaaaaaaaaaaaaa", "lol"};
    int correctAnswers[3] = {0, -1, 1};
    for (int i = 0; i < 3; ++i) {
        int error = 0;
        int answer = findPositionInFile("../testData", samplePatterns[i], &error);
        if (error == 1) {
            return false;
        }
        if (answer != correctAnswers[i]) {
            return false;
        }
    }
    return true;
}