#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define SIZE 32

void binaryRepresentation(int number, int *binaryNumber) {
    int bit = 0b01000000000000000000000000000000;
    binaryNumber[0] = (number < 0) ? 1 : 0;
    for (int i = 1; i < SIZE; ++i) {
        binaryNumber[i] = (bit & number) ? 1 : 0;
        bit = bit >> 1;
    }
}

int binaryAddition(int *firstNumber, int *secondNumber, int *result, bool *isNegative) {
    int carrier = 0;
    for (int i = SIZE - 1; i >= 0; --i) {
        result[i] =(((firstNumber[i] + secondNumber[i] + carrier) % 2) == 1) ? 1 : 0;
        carrier = ((firstNumber[i] + secondNumber[i] + carrier) > 1) ? 1 : 0;
    }
    *isNegative = (result[0] == 1);
    return carrier;
}

bool testRepresentation(void) {
    int testNumbers[4] = {12, 23, -12, -23};
    int correctAnswers[4][SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1,
                                    1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,
                                    1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,0,1,0,0,1};
    for (int i = 0; i < 4; ++i) {
        int binaryNumber[SIZE] = {0};
        binaryRepresentation(testNumbers[i], binaryNumber);
        for (int j = 0; j < SIZE; ++j) {
            if (!(binaryNumber[j] == correctAnswers[i][j])) {
                return false;
            }
        }
    }
    return true;
}

int testAddition(void) {
    int testNumberFirst[SIZE] = {1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0};
    int testNumberSecond[SIZE] = {1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,0,1,0,0,1};
    int correctAnswer[SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
                                   1, 1, 0, 1};
    int result[SIZE] = {0};
    bool isNegative = false;
    bool isNegativeFirst = (testNumberFirst[0] == 1);
    bool isNegativeSecond = (testNumberSecond[0] == 1);
    binaryAddition(testNumberFirst, testNumberSecond, result, &isNegative);
    for (int j = 0; j < SIZE; ++j) {
        if (!(result[j] == correctAnswer[j])) {
            return 2;
        }
    }
    if (!isNegative) {
        if (isNegativeFirst && isNegativeSecond) {
            return 1;
        }
    } else {
        if ((!isNegativeFirst) && (!isNegativeSecond)) {
            return 1;
        }
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "Rus");
    if (!testRepresentation()) {
        printf("%s", "Неверный перевод в двоичную систему\n");
        return 1;
    }
    int errorCode = testAddition();
    if (errorCode == 1) {
        printf("Произошло переполнение\n");
        return 1;
    } else if (errorCode == 2) {
        printf("Неверный ответ при суммировании\n");
        return 1;
    }
    printf("Введите два числа в диапазоне [-2^31, 2^31 - 1]:\n");
    int firstNumber = 0;
    int secondNumber = 0;
    scanf("%d%d", &firstNumber, &secondNumber);
    bool isNegativeFirst = (firstNumber < 0);
    bool isNegativeSecond = (secondNumber < 0);
    int binaryFirstNumber[SIZE] = {0};
    binaryRepresentation(firstNumber, binaryFirstNumber);
    for (int i = 0; i < SIZE; ++i) {
        printf("%d", binaryFirstNumber[i]);
    }
    printf("%s", "\n");
    int binarySecondNumber[SIZE] = {0};
    binaryRepresentation(secondNumber, binarySecondNumber);
    for (int i = 0; i < SIZE; ++i) {
        printf("%d", binarySecondNumber[i]);
    }
    printf("%s", "\n");
    int result[SIZE] = {0};
    bool isNegative = false;
    int carrier = binaryAddition(binaryFirstNumber, binarySecondNumber, result, &isNegative);
    if (!isNegative) {
        if (isNegativeFirst && isNegativeSecond) {
            printf("Произошло переполнение\n");
            return 1;
        }
    } else {
        if ((!isNegativeFirst) && (!isNegativeSecond)) {
            printf("Произошло переполнение\n");
            return 1;
        }
    }
    if (carrier == 1) {
        printf("Произошел перенос\n");
    }

    for (int i = 0; i < SIZE; ++i) {
        printf("%d", result[i]);
    }
    return 0;
}
