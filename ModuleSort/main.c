#include <stdio.h>
#include <stdbool.h>
#include "countingSort.h"

int mostFrequentElement(int * data, int size) {
    int minimalValue = findMinValue(data, size);
    int maximalValue = findMaxValue(data, size);
    countingSort(data, maximalValue - minimalValue + 1);
    int maximum = data[0];
    int countCurrentCoincide = 1;
    int maxCount = 0;
    for (int i = 0; i < size - 1; ++i) {
        if (data[i] == data[i + 1]) {
            ++countCurrentCoincide;
        } else {
            if (countCurrentCoincide > maxCount) {
                maxCount = countCurrentCoincide;
                maximum = data[i];
            }
            countCurrentCoincide = 1;
        }
    }
    return maximum;
}

bool test(void) {
    int testEvenCase [10] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    int correctAnswer = 3;
    int answer = mostFrequentElement(testEvenCase, 10);
    if (!(correctAnswer == answer)) {
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
    if (!(correctAnswer == answer)) {
        return false;
    }

    return true;
}

int main() {
    if (!(test())) {
        printf("%s", "Tests have been failed\n");
        return 1;
    }
    printf("%s", "Tests have been passed successfully\n");
    return 0;
}
