#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int fibonacciRecursion(int index, int *result) {
    if (index < 1) {
        return 1;
    }

    if (index <= 2) {
        *result = 1;
        return 0;
    }
    int firstNumber = 0;
    int errorCodeFirst = fibonacciRecursion(index - 2, &firstNumber);
    int secondNumber = 0;
    int errorCodeSecond = fibonacciRecursion(index - 1, &secondNumber);
    if (errorCodeFirst + errorCodeSecond) {
        return 1;
    }
    *result = firstNumber + secondNumber;
    return 0;
}

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

bool testFibonacci(bool type) {
    int result = 0;

    int correctSequence[26] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610,
                               987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025};
    if (type) {
        for (int i = 1; i <= 25; ++i) {
            int errorCode = fibonacciRecursion(i, &result);
            if (errorCode) {
                return false;
            }
            if (result == correctSequence[i]){
                continue;
            } else {
                return false;
            }
        }
        return true;
    } else {
        for (int i = 1; i <= 25; ++i) {
            int errorCode = fibonacciIterative(i, &result);
            if (errorCode) {
                return false;
            }
            if (result == correctSequence[i]){
                continue;
            } else {
                return false;
            }
        }
        return true;
    }
}

int main() {
    bool testAreCorrect = true;
    if (testFibonacci(true)) {
        printf("%s", "Recursion is correct\n");
    } else {
        printf("%s", "Recursion is incorrect\n");
        testAreCorrect = false;
    }

    if (testFibonacci(false)) {
        printf("%s", "Iterative algorithm is correct\n");
    } else {
        printf("%s", "Iterative algorithm is incorrect\n");
        testAreCorrect = false;
    }

    if (!testAreCorrect) {
        return 1;
    }

    long double difference = 0;
    int number = 1;
    while (difference < CLOCKS_PER_SEC) {

        int result = 0;
        clock_t timeStartRecursion = clock();
        int errorCode = fibonacciRecursion(number, &result);
        if (errorCode) {
            printf("%s", "Something went wrong");
            break;
        }
        clock_t timeEndRecursion = clock();

        clock_t timeStartIterative = clock();
        errorCode = fibonacciIterative(number++, &result);
        if (errorCode) {
            printf("%s", "Something went wrong");
            break;
        }
        clock_t timeEndIterative = clock();

        difference = (long double) abs((timeEndRecursion - timeStartRecursion) - (timeEndIterative - timeStartIterative));
    }

    --number;
    printf("%s%d%s", "The number ", number, " is calculated significantly longer by recursion\n");
}
