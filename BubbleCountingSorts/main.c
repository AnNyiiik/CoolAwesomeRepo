#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define SIZE 100000
#define TEST_SIZE 100000

void mySwap(int *temp1, int *temp2) {
    *temp1 = *temp1 + *temp2;
    *temp2 = *temp1 - *temp2;
    *temp1 = *temp1 - *temp2;
}

void bubbleSort(int *data, int size) {
    if (size == 0) {
        return;
    }
    for (int i = 0; i < size - 1; ++i) {
        for (int j = size - 2; j >= i; --j) {
            if (data[j] > data[j + 1]) {
                mySwap(data + j, data + j + 1);
            }
        }
    }
}

int findMinValue(int *data, int size) {
    int minValue = data[0];
    for (int i = 0; i < size; ++i) {
        if (data[i] < minValue) {
            minValue = data[i];
        }
    }
    return minValue;
}

int findMaxValue(int *data, int size) {
    int maxValue = data[0];
    for (int i = 0; i < size; ++i) {
        if (data[i] > maxValue) {
            maxValue = data[i];
        }
    }
    return maxValue;
}

int countingSort(int *data, int size) {
    const int minimalValue = findMinValue(data, size);
    const int maximalValue = findMaxValue(data, size);
    int * countArray = (int*)calloc(maximalValue - minimalValue + 1, sizeof(int));
    if (countArray == NULL) {
        return 1;
    }
    for (int i = 0; i < size; ++i) {
        countArray[data[i] - minimalValue] ++;
    }
    int index = 0;
    for (int i = 0; i < maximalValue - minimalValue + 1; ++i) {
        if (countArray[i] > 0) {
            int k = 0;
            while (k < countArray[i]) {
                data[index] = i + minimalValue;
                ++index;
                ++k;
            }
        }
    }
    free(countArray);
    return 0;
}

bool testSort(bool type) {
    int oneElementCase[1] = {8};
    if (type) {
        bubbleSort(oneElementCase, 1);
    } else {
        countingSort(oneElementCase, 1);
    }

    if (oneElementCase[0] != 8) {
        return false;
    }

    int testingData[TEST_SIZE] = {74, 65, 36, 46, 53, 34, 65, 85, 32, 78,
                                  25,95, 96, 91, 55, 34, 66, 32, 67, 84,
                                  45, 17, 48, 53, 65, 69, 78, 69, 46, 67,
                                  16, 13, 8, 21, 81, 20, 52, 33, 64, 56,
                                  32, 100, 46, 21, 28, 51, 44, 85, 66, 17,
                                  92, 39, 89, 67, 78, 58, 75, 15, 11, 1,
                                  2, 68, 42, 91, 43, 44, 61, 19, 61, 64,
                                  29, 9, 42, 93, 36, 39, 3, 1, 56, 69,
                                  68, 49, 9, 8, 10, 3, 75, 85, 89, 63,
                                  89, 3, 72, 18, 33, 75, 21, 79, 51, 42};

    if (type) {
        bubbleSort(testingData, TEST_SIZE);
    } else {
        countingSort(testingData, TEST_SIZE);
    }
    for (int i = 0; i < 99; ++i) {
        if (testingData[i] > testingData[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    bool allSortingsFine = true;

    if (testSort(true)) {
        printf("%s", "The bubble sort is correct\n");
    } else {
        printf("%s", "The bubble sort is incorrect\n");
        allSortingsFine = false;
    }
    if (testSort(false)) {
        printf("%s", "The counting sort is correct\n");
    } else {
        printf("%s", "The counting sort is incorrect\n");
        allSortingsFine = false;
    }

    if (allSortingsFine) {
        int arrayBubble[SIZE] = {0};
        int arrayCounting[SIZE] = {0};
        for (int i = 0; i < SIZE; ++i) {
            arrayBubble[i] = rand() % 1000;
            arrayCounting[i] = arrayBubble[i];

        }
        clock_t timeStartBubble = clock();
        bubbleSort(arrayBubble, SIZE);
        clock_t timeFinishBubble = clock();
        clock_t timeBubble = timeFinishBubble - timeStartBubble;

        clock_t timeStartCounting = clock();
        int errorCode = countingSort(arrayCounting, SIZE);
        if (errorCode == 1) {
            printf("%s", "The memory wasn't allocated.\n");
        }
        clock_t timeFinishCounting = clock();
        clock_t timeCounting = timeFinishCounting - timeStartCounting;

        for (int i = 0; i < SIZE; ++i) {
            printf("%d%s", arrayBubble[i], " ");
        }

        printf("%s%Lf%s", "\nThe time of Bubble sort is ", (long double)timeBubble / CLOCKS_PER_SEC, " seconds.");
        printf("%s%Lf%s", "\nThe time of Counting sort is ", (long double)timeCounting / CLOCKS_PER_SEC, " seconds.");
        printf("%s%Lf%s", "\nThe difference is ", (long double) (timeBubble - timeCounting) / CLOCKS_PER_SEC, " seconds.\n");

        if (testSort(true)) {
            printf("%s", "The bubble sort is correct\n");
        } else {
            printf("%s", "The bubble sort is incorrect\n");
        }
        if (testSort(false)) {
            printf("%s", "The counting sort is correct\n");
        } else {
            printf("%s", "The counting sort is incorrect\n");
        }
    }
}

