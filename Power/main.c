#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

float powerLinear(int base, int exponent, int *errorCode) {
    if ((base == 0) && (exponent <= 0)){
        *errorCode = 1;
        return 1;
    }
    if (exponent == 0) {
        *errorCode = 0;
        return 1;
    }

    float answer = 1;

    if (exponent > 0) {
        for (int i = 0; i < exponent; ++i) {
            answer = answer * base;
        }
        *errorCode = 0;
        return answer;
    }

    for (int i = 0; i < -exponent; ++i) {
        answer = answer / base;
    }
    *errorCode = 0;
    return answer;
}

float powerLog(float base, int exponent, int *errorCode) {
    if ((base == 0) && (exponent <= 0)){
        *errorCode = 1;
        return 1;
    }

    if (exponent == 0) {
        *errorCode = 0;
        return 1;
    }

    if (base == 0) {
        *errorCode = 0;
        return 0;
    }

    if (exponent < 0) {
        exponent = -exponent;
        base = 1 / base;
    }

    float answer = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            answer = answer * base;
        }
        base = base * base;
        exponent = exponent / 2;
    }
    *errorCode = 0;
    return answer;
}

bool testExponentCalculation(bool type) {
    if (type) {
        int errorCode = 0;
        if ((powerLinear(0, rand() % 10 + 1, &errorCode) != 0) || (powerLinear(1, rand() % 10, &errorCode) != 1) || (powerLinear(rand() % 10 + 1, 0, &errorCode) != 1)) {
            return false;
        }
    } else {
        int errorCode = 0;
        if ((powerLog(0, rand() % 10 + 1, &errorCode) != 0) || (powerLog(1, rand() % 10, &errorCode) != 1) || (powerLog(rand() % 10 + 1, 0, &errorCode) != 1)) {
            return false;
        }
    }

    int correctAnswersPositiveExponent[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    float correctAnswersNegativeExponent[6] = {1, 0.5, 0.25, 0.125, 0.0625, 0.03125};
    if (type) {
        for (int i = 1; i < 10; ++i) {
            int errorCode = 0;
            if (powerLinear(2, i, &errorCode) != correctAnswersPositiveExponent[i]) {
                return false;
            }
        }
        for (int i = -1; i > -6; --i) {
            int errorCode = 0;
            if (powerLinear(2, i, &errorCode) != correctAnswersNegativeExponent[-i]) {
                return false;
            }
        }
        return true;
    } else {
        for (int i = 1; i < 10; ++i) {
            int errorCode = 0;
            if (powerLog(2, i,&errorCode) != correctAnswersPositiveExponent[i]) {
                return false;
            }
        }
        for (int i = -1; i > -6; --i) {
            int errorCode = 0;
            if (powerLog(2, i, &errorCode) != correctAnswersNegativeExponent[-i]) {
                return false;
            }
        }
        return true;
    }
}

int main() {
    if (testExponentCalculation(true)) {
        printf("%s", "Linear algorithm is correct\n");
    } else {
        printf("%s", "Linear algorithm is incorrect\n");
    }

    if (testExponentCalculation(false)) {
        printf("%s", "Logarithmic algorithm is correct\n");
    } else {
        printf("%s", "Logarithmic algorithm is incorrect\n");
    }
}
