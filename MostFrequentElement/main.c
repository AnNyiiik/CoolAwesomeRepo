#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
        while (data[right] > bound && (right > 0)) {
            --right;
        }
        if (left <= right) {
            if (data[left] != data[right]){
                if (data[left] != data[right]){
                    data[left] = data[left] ^ data[right];
                    data[right] = data[right] ^ data[left];
                    data[left] = data[left] ^ data[right];
                }
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
    for (int i = 99; i >= 0 ; --i) {
        data[i] = 99 - i;
    }
    smartQuickSort(data, 0, 99);
    for (int i = 0; i < 100; ++i) {
        if (data[i] != i) {
            return false;
        }
    }
    return true;
}

int mostFrequentElement(int *data, int size) {
    if (size == 1) {
        return data[0];
    }
    smartQuickSort(data, 0, size - 1);
    int maxLength = 1;
    int currentLength = 1;
    int element = data[0];
    for (int i = 0; i < size - 1; ++i) {
        if (data[i] == data[i + 1]) {
            ++currentLength;
        } else {
            if (currentLength > maxLength) {
                maxLength = currentLength;
                element = data[i];
            }
            currentLength = 1;
        }
    }
    if (currentLength > maxLength) {
        element = data[size - 1];
    }
    return element;
}

bool test(void) {
    int testEvenCase [10] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    int correctAnswer = 3;
    int answer = mostFrequentElement(testEvenCase, 10);
    if (correctAnswer != answer) {
        return false;
    }
    int testUnevenCase [100] = {74, 65, 36, 46, 53, 34, 65, 85, 32, 78,
    25,95, 96, 91, 55, 34, 66, 32, 67, 84,
    45, 17, 48, 53, 65, 69, 78, 69, 46, 67,
    16, 13, 8, 21, 81, 20, 52, 33, 64, 56,
    32, 100, 46, 21, 28, 51, 44, 85, 66, 17,
    92, 39, 89, 67, 78, 58, 75, 15, 11, 1,
    2, 68, 42, 91, 43, 44, 61, 19, 61, 64,
    29, 9, 42, 93, 36, 39, 3, 1, 56, 69,
    68, 49, 9, 8, 10, 3, 75, 85, 89, 63,
    89, 3, 72, 18, 33, 75, 21, 79, 51, 42};
    correctAnswer = 3;
    answer = mostFrequentElement(testUnevenCase, 100);
    return correctAnswer == answer;
}

int main() {
    if (!testQuickSort()) {
        return 1;
    }
    if (!test()) {
        printf("%s", "Tests have been failed\n");
        return 1;
    }
    printf("%s", "Tests have been passed successfully\n");
    return 0;
}
