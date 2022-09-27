#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE_DATA 100000

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

int main() {
    if(!testQuickSort()) {
        printf("%s", "Tests are incorrect!\n");
        return 1;
    }
    printf("%s", "Tests are correct!\n");
    int data[SIZE_DATA] = {0};
    for (int i = 0; i < SIZE_DATA; ++i) {
        data[i] = rand() % 10000 - 5000;
    }
    smartQuickSort(data, 0, SIZE_DATA - 1);
    for (int i = 0; i < SIZE_DATA; ++i) {
        printf("%d%s", data[i], " ");
    }
    return 0;
}

