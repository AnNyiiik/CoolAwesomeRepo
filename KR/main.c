#include <stdio.h>
#include <stdbool.h>

int fibonacciIterative(int index, int *result) {
    if (index < 1) {
        return 1;
    }

    if (index <= 2) {
        *result = 1;
        return 0;
    }

    int maximum = 2;
    int minimum = 1;

    for (int i = 0; i < index - 3; ++i) {
        maximum = maximum + minimum;
        minimum = maximum - minimum;
    }

    *result = maximum;
    return 0;
}

int fibonacciSumEven(void) {
    int sum = 0;
    int index = 0;
    int number = 0;
    fibonacciIterative(index, &number);
    while(number < 1000000) {
        if (number % 2) {
            sum = sum + number;
        }
        ++index;
        fibonacciIterative(index, &number);
    }
    return sum;
}
bool test(void) {
    int correctAnswer = 1089154;
    return (fibonacciSumEven() == correctAnswer);
}

int main() {
    if (!test()) {
        printf("%s", "The answer is incorrect, test failed");
        return 1;
    }
    printf("%s%d", "The answer is ", fibonacciSumEven());
    return 0;
}
