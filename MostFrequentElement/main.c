int findMinValue(int * data, int size) {
    int minValue = data[0];
    for (int i = 0; i < size; ++i) {
        if (data[i] < minValue) {
            minValue = data[i];
        }
    }
    return minValue;
}

int findMaxValue(int * data, int size) {
    int maxValue = data[0];
    for (int i = 0; i < size; ++i) {
        if (data[i] > maxValue) {
            maxValue = data[i];
        }
    }
    return maxValue;
}
