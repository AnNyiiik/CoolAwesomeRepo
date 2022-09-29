#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void insertionSort(int *data, int start, int end)
{
    for (int i = start + 1; i <= end; i++)
    {
        int index = i - 1;
        while(index >= start && (data[index] > data[index + 1]))
        {
            data[index + 1] = data[index + 1] ^ data[index];
            data[index] = data[index] ^ data[index + 1];
            data[index + 1] = data[index + 1] ^ data[index];
            index--;
        }
    }
}

void smartQuickSort(int *data, int start, int end) {
    if (start >= end) {
        return;
    }

    if (end - start + 1 <= 10) {
        insertionSort(data, start, end);
        return;
    }

    int bound = data[(start + end) / 2];
    int left = start;
    int right = end;

    while (left <= right) {
        while (data[left] < bound) {
            ++left;
        }
        while ((data[right] > bound) && (right > 0)) {
            --right;
        }
        if (left <= right) {
            if (data[left] != data[right]){
                data[left] = data[left] ^ data[right];
                data[right] = data[right] ^ data[left];
                data[left] = data[left] ^ data[right];
            }
            ++left;
            --right;
        }
    }
    smartQuickSort(data, start, right);
    smartQuickSort(data, left, end);
}

bool testQuickSort(void) {
    int data[100] = {0};
    for (int i = 0; i < 100; ++i) {
        data[i] = rand() % 100 - 50;
    }
    smartQuickSort(data, 0, 99);
    for (int i = 0; i < 99; ++i) {
        if (data[i] > data[i + 1]) {
            return false;
        }
    }
    return true;
}

bool binarySearch(int target, int *data, int size) {
    if (size == 0) {
        return false;
    }
    int left = 0;
    int right = size;
    while (left < right - 1) {
        int mediana = (left + right) / 2;
        if (target < data[mediana]) {
            right = mediana;
        } else {
            left = mediana;
        }
    }
    if (data[left] == target) {
        return true;
    }
    return false;
}

bool testBinarySearch(void) {
    int testEmptyCase[0] = {};
    if (binarySearch(rand() % 100 - 50, testEmptyCase, 0)) {
        return false;
    }
    int testNormalCase[100] = {74, 65, 36, 46, 53, 34, 65, 85, 32, 78,
                               25,95, 96, 91, 55, 34, 66, 32, 67, 84,
                               45, 17, 48, 53, 65, 69, 78, 69, 46, 67,
                               16, 13, 8, 21, 81, 20, 52, 33, 64, 56,
                               32, 100, 46, 21, 28, 51, 44, 85, 66, 17,
                               92, 39, 89, 67, 78, 58, 75, 15, 11, 1,
                               2, 68, 42, 91, 43, 44, 61, 19, 61, 64,
                               29, 9, 42, 93, 36, 39, 3, 1, 56, 69,
                               68, 49, 9, 8, 10, 3, 75, 85, 89, 63,
                               89, 3, 72, 18, 33, 75, 21, 79, 51, 42};
    smartQuickSort(testNormalCase, 0, 99);
    for (int i = 0; i < 100; ++i) {
        if (!(binarySearch(testNormalCase[i], testNormalCase, 100))) {
            return false;
        }
    }
    return true;

}

int main() {
    if (!(testQuickSort())) {
        printf("%s", "Sort is incorrect");
        return 1;
    }
    if (!(testBinarySearch())) {
        printf("%s", "Search is incorrect");
        return 1;
    }
    printf("%s", "Search is correct\n");
    printf("%s", "Please, enter n and k:\n");
    int numberOfElements = 0;
    int numberOfSearchedElements = 0;
    scanf("%d%d", &numberOfElements, &numberOfSearchedElements);
    int * data = (int*)calloc(numberOfElements, sizeof(int));
    for (int i = 0; i < numberOfElements; ++i) {
        data[i] = rand() % 10 - 5;
        printf("%d%s", data[i], " ");
    }
    printf("%s", "\n");
    int * targets = (int*)calloc(numberOfSearchedElements, sizeof(int));
    for (int i = 0; i < numberOfSearchedElements; ++i) {
        targets[i] = rand() % 10 - 5;
        printf("%d%s", targets[i], " ");
    }
    for (int i = 0; i < numberOfSearchedElements; ++i) {
        if (binarySearch(targets[i], data, numberOfElements)) {
            printf("%s%d%s", "The element ", targets[i], " is in data.\n");
        } else {
            printf("%s%d%s", "The element ", targets[i], " isn't in data.\n");
        }
    }
    free(data);
    free(targets);
    return 0;
}
