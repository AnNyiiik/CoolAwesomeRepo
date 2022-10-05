#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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

bool testReadComments(void) {
    const char correctSequence[18] = ";jasijioijaioijsio";
    FILE *file = fopen("/Users/annnikolaeff/CoolAwesomeRepo/KR/testData", "r");
    if (file == NULL) {
        printf("%s", "file not found!");
        return 1;
    }
    while (!feof(file)) {
        char *buffer = malloc(sizeof(char) * 100);
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0) {
            free(buffer);
            break;
        }
        if (buffer[0] == ';') {
            for (int i = 0; i < 18; ++i) {
                if (buffer[i] != correctSequence[i]) {
                    free(buffer);
                    fclose(file);
                    return false;
                }
            }
        }
        free(buffer);
    }
    fclose(file);
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
    if (!testReadComments()) {
        printf("%s", "The answer is incorrect, test failed");
        return 1;
    }
    FILE *file = fopen("/Users/annnikolaeff/CoolAwesomeRepo/KR/data.txt", "r");
    if (file == NULL) {
        printf("%s", "file not found!");
        return 1;
    }

    while (!feof(file)) {
        char *buffer = malloc(sizeof(char) * 100);
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0) {
            free(buffer);
            break;
        }
        if (buffer[0] == ';') {
            printf("%s%s", buffer, "\n");
        }
        free(buffer);
    }
    fclose(file);

    return 0;
}
