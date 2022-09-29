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
//    int testNormalCase[100] =

}

int main() {
    if (!(testQuickSort())) {
        printf("%s", "Sort is incorrect");
        return 1;
    }
    printf("%s", "Sort is correct");
    return 0;
}
