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
