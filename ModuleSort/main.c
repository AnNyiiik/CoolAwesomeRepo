#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

int readFromFile(const char *fileName, int *data, int *size) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return 1;
    }
    int linesRead = 0;
    while (!feof(file)) {
        char buffer[32] = {0};
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0) {
            break;
        }
        char *number = strtok(buffer, ",");
        data[linesRead] = atoi(number);
        ++linesRead;
    }
    *size = linesRead;
    fclose(file);
    return 0;
}

int mostFrequentElement(const char *fileName) {
    int data[10000] = {0};
    int size = 0;
    readFromFile(fileName, data, &size);
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
    return mostFrequentElement("../sourceData") == 7;
}

int main() {
    if (!test() || !testQuickSort()) {
        printf("%s", "Tests have been failed\n");
        return 1;
    }
    printf("%s", "Tests have been passed successfully\n");
    int answer = mostFrequentElement("../sourceData");
    printf("%s%d", "The most frequent element is ", answer);
    return 0;
}
