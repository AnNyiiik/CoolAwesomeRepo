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

void mySwap(int *temp1, int *temp2) {
    if (temp1 != temp2){
        *temp1 = *temp1 + *temp2;
        *temp2 = *temp1 - *temp2;
        *temp1 = *temp1 - *temp2;
    }
}

void selectionSort(int *data, int size) {
    for (int i = 0; i < size - 1; i = i + 2) {
        int minimal = data[i];
        int minimalIndex = i;
        for (int j = i + 2; j < size; j = j + 2) {
            if (minimal > data[j]) {
                minimal = data[j];
                minimalIndex = j;
            }
        }
        mySwap((data + i), (data + minimalIndex));
    }
    return;
}

bool testSort(void) {
    int array[5] = {5, 4, 3, 2, 1};
    int correctSequence[5] = {1, 4, 3, 2, 5};
    selectionSort(array, 5);
    for (int i = 0; i < 5; ++i) {
        if (correctSequence[i] != array[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    if (!test()) {
        printf("%s", "The answer is incorrect, test failed");
        return 1;
    }
    printf("%s%d", "The answer is ", fibonacciSumEven());

    if (!testSort()) {
        printf("%s", "The answer is incorrect, test failed");
        return 1;
    }
    int array[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; //{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    selectionSort(array, 10);
    for (int i = 0; i < 10; ++i) {
        printf("%d%s", array[i], " ");
    }

    return 0;
}
