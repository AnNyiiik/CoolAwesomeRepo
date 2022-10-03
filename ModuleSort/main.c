#include <stdio.h>
#include <stdlib.h>
#include "countingSort.h"

int mostFrequentElement(int * data, int size) {
    int minimalValue = findMinValue(data, size);
    int maximalValue = findMaxValue(data, size);
    int * countArray = (int*) calloc(maximalValue - minimalValue + 1, sizeof(int));
    countingSort(countArray, maximalValue - minimalValue + 1);
    int maximum = 0;
    int maximumIndex = 0;
    for (int i = 0; i < maximalValue - minimalValue + 1; ++i) {
        if (countArray[i] > maximumIndex) {
            maximum = i + minimalValue;
            maximumIndex = countArray[i];
        }
    }
    free(countArray);
    return maximum;
}

int main() {

}
