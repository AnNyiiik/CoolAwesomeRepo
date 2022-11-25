#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int readFromFile(FILE *file, int *data, int *size) {
    if (file == NULL) {
        return 1;
    }
    int linesRead = 0;
    while (!feof(file)) {
        char *buffer = malloc(sizeof(char) * 32);
        if (buffer == NULL) {
            fclose(file);
            return 1;
        }
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0) {
            free(buffer);
            break;
        }
        char *number = strtok(buffer, ",");
        data[linesRead] = atoi(number);
        ++linesRead;
        free(buffer);
    }
    *size = linesRead;
    fclose(file);
    return 0;
}

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
int mostFrequentElement(FILE *file) {
    int data[10000] = {0};
    int size = 0;
    readFromFile(file, data, &size);
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
    FILE *file = fopen("../sourceData", "r");
    if (file == NULL) {
        return false;
    }
    return mostFrequentElement(file) == 7;
}

