#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define SIZE (sizeof(int) * 8)

void printArray(const int *binaryArray);

void convertToBinary(int number, int *binaryNumber) {
    int bit = 1;
    for (int i = SIZE - 1; i >= 0; --i) {
        binaryNumber[i] = (bit & number) ? 1 : 0;
        bit <<= 1;
    }
}

int convertToDecimal(const int *binaryArray) {
    int base = 1;
    int decimal = 0;
    for (int i = SIZE - 1; i >= 0; --i) {
        decimal += base * binaryArray[i];
        base = base * 2;
    }
    return decimal;
}

int binaryAddition(int const *firstNumber, int const *secondNumber, int *result) {
    int carrier = 0;
    for (int i = SIZE - 1; i >= 0; --i) {
        result[i] = (firstNumber[i] + secondNumber[i] + carrier) % 2;
        carrier = (firstNumber[i] + secondNumber[i] + carrier) / 2;
    }
    return carrier;
}

bool testRepresentation(void) {
    int testNumbers[4] = {12, 23, -12, -23};
    int correctAnswers[4][SIZE] = {0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1,
   0, 0,

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 1, 1, 1,

    1, 1, 1, 1, 1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,0,1,0,0,

    1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,
    1,1,1,1,1,0,1,0,0,1};
    for (int i = 0; i < 4; ++i) {
        int binaryNumber[SIZE] = {0};
        convertToBinary(testNumbers[i], binaryNumber);
        for (int j = 0; j < SIZE; ++j) {
            if (binaryNumber[j] != correctAnswers[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool testDecimalRepresentation(void) {
    int negative[SIZE] = {1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,
                          1,1,1,1,1,1,1,1,1,1,1,1,
                          1,1,1,0,1,0,0};
    if (convertToDecimal(negative) != -12) {
        return false;
    }
    int positive[SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 1, 1, 0, 0};
    return convertToDecimal(positive) == 12;
}

int testAddition(void) {
    int testNumberFirst[SIZE] = {1, 1, 1, 1, 1,1,1,1,1,1,1,1,
                                 1,1,1,1,1,1,1,1,1,1,1,1,
                                 1,1,1,1,0,1,0,0};
    int testNumberSecond[SIZE] = {1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1,
                                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                  1,1,1,1,1,1,0,1,0,0,1};
    int correctAnswer[SIZE] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                               1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                               1, 1, 1, 1, 1, 0, 1,
                                   1, 1, 0, 1};
    int result[SIZE] = {0};
    binaryAddition(testNumberFirst, testNumberSecond, result);
    for (int j = 0; j < SIZE; ++j) {
        if (result[j] != correctAnswer[j]) {
            return 2;
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
    if (!testDecimalRepresentation()) {
        printf("%s", "Неверный перевод в десятичную систему\n");
        return 1;
    }
    int errorCode = testAddition();
    if (errorCode == 2) {
        printf("Неверный ответ при суммировании\n");
        return 1;
    }
    printf("Введите два числа в диапазоне [-2^31, 2^31 - 1]:\n");
    int firstNumber = 0;
    int secondNumber = 0;
    scanf("%d%d", &firstNumber, &secondNumber);
    int binaryFirstNumber[SIZE] = {0};
    convertToBinary(firstNumber, binaryFirstNumber);
    printArray(binaryFirstNumber);
    printf("%s", "\n");
    int binarySecondNumber[SIZE] = {0};
    convertToBinary(secondNumber, binarySecondNumber);
    printArray(binarySecondNumber);
    printf("%s", "\n");
    int result[SIZE] = {0};
    int carrier = binaryAddition(binaryFirstNumber, binarySecondNumber, result);
    if (carrier == 1) {
        printf("Произошел перенос\n");
    }

    for (int i = 0; i < SIZE; ++i) {
        printf("%d", result[i]);
    }
    printf("\n%d", convertToDecimal(result));
    return 0;
}

void printArray(const int *binaryNumber) {
    for (int i = 0; i < SIZE; ++i) {
        printf("%d", binaryNumber[i]);
    }
}
