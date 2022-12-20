#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 100000
#define TEST_SIZE 100

void mySwap(int *temp1, int *temp2) {
    if (temp1 != temp2){
        *temp1 = *temp1 + *temp2;
        *temp2 = *temp1 - *temp2;
        *temp1 = *temp1 - *temp2;
    }
}

void halfQuickSort(int *data, int size) {
    if (size <= 0) {
        return;
    }
    const int firstElement = data[0];
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        while (data[left] < firstElement) {
            ++left;
        }
        while ((data[right] >= firstElement) && (right > 0)) {
            --right;
        }
        if (left <= right) {
            mySwap(data + left, data + right);
            ++left;
            --right;
        }
    }
}

bool testHalfQuickSort(void) {
    int oneElementCase[1] = {8};
    halfQuickSort(oneElementCase, 1);

    if (oneElementCase[0] != 8) {
        return false;
    }

    int testData[TEST_SIZE] = {74, 65, 36, 46, 53, 34, 65, 85, 32, 78,
                               25,95, 96, 91, 55, 34, 66, 32, 67, 84,
                               45, 17, 48, 53, 65, 69, 78, 69, 46, 67,
                               16, 13, 8, 21, 81, 20, 52, 33, 64, 56,
                               32, 100, 46, 21, 28, 51, 44, 85, 66, 17,
                               92, 39, 89, 67, 78, 58, 75, 15, 11, 1,
                               2, 68, 42, 91, 43, 44, 61, 19, 61, 64,
                               29, 9, 42, 93, 36, 39, 3, 1, 56, 69,
                               68, 49, 9, 8, 10, 3, 75, 85, 89, 63,
                               89, 3, 72, 18, 33, 75, 21, 79, 51, 42};

    const int firstElement = testData[0];
    halfQuickSort(testData, TEST_SIZE);
    int index = 0;
    while ((testData[index] < firstElement) && (index < TEST_SIZE - 1)) {
        ++index;
    }
    for (int i = index; i < TEST_SIZE; ++i) {
        if (testData[i] < firstElement) {
            return false;
        }
    }
    return true;
}

int main() {
    if (!(testHalfQuickSort())) {
        printf("%s", "Sorting algorithm is incorrect\n");
        return 1;
    }
    printf("%s", "Sorting algorithm is correct\n");
    int data[SIZE] = {0};
    for (int i = 0; i < SIZE; ++i) {
        data[i] = rand() % 10000 - 5000;
    }
    halfQuickSort(data, SIZE);
    for (int i = 0; i < SIZE; ++i) {
        printf("%d%s", data[i], " ");
    }
    return 0;
}

