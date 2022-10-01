#include <stdio.h>
#include <locale.h>

void binaryRepresentation(int number, char *binaryNumber) {
    int bit = 0b10000000;

    for (int i = 0; i < 8; ++i) {
        binaryNumber[7 - i] = (bit & number) ? 1 : 0;
        bit = bit >> 1;
    }
    for (int i = 7; i >= 0; --i) {
        printf("%d", binaryNumber[i]);
    }
    return;
}
int main() {
    setlocale(LC_ALL, "Rus");
    printf("Введите два числа:\n");
    int firstNumber = 0;
    //int secondNumber = 0;
    scanf("%d", &firstNumber);
    int *binaryNumber[8] = {0};
    binaryRepresentation(firstNumber, binaryNumber);

    return 0;
}
