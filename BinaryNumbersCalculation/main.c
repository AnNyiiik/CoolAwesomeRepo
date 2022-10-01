#include <stdio.h>
#include <locale.h>

void binaryRepresentation(int number, int *binaryNumber) {
    int bit = 0b01000000000000000000000000000000;
    binaryNumber[0] = (number < 0) ? 1 : 0;
    for (int i = 1; i < 32; ++i) {
        *(binaryNumber + i) = (bit & number) ? 1 : 0;
        bit = bit >> 1;
    }
}

void binaryAddition(int *firstNumber, int *secondNumber, int *result) {
    int carrier = 0;
    for (int i = 31; i >= 0; --i) {
        result[i] = (((firstNumber[i] + secondNumber[i] + carrier) % 2) == 1) ? 1 : 0;
        carrier = ((firstNumber[i] + secondNumber[i] + carrier) > 1) ? 1 : 0;
    }

    return;
}

int main() {
    setlocale(LC_ALL, "Rus");
    printf("Введите два числа:\n");
    int firstNumber = 0;
    int secondNumber = 0;
    scanf("%d%d", &firstNumber, &secondNumber);
    int binaryFirstNumber[32] = {0};
    binaryRepresentation(firstNumber, binaryFirstNumber);
    for (int i = 0; i < 32; ++i) {
        printf("%d", binaryFirstNumber[i]);
    }
    printf("%s", "\n");
    int binarySecondNumber[32] = {0};
    binaryRepresentation(secondNumber, binarySecondNumber);
    for (int i = 0; i < 32; ++i) {
        printf("%d", binarySecondNumber[i]);
    }
    printf("%s", "\n");
    int result[32] = {0};
    binaryAddition(binaryFirstNumber, binarySecondNumber, result);
    for (int i = 0; i < 32; ++i) {
        printf("%d", result[i]);
    }
    return 0;
}
