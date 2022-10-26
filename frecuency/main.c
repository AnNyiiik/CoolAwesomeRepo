#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

void mySwap(int *temp1, int *temp2) {
    if (temp1 != temp2){
        *temp1 = *temp1 + *temp2;
        *temp2 = *temp1 - *temp2;
        *temp1 = *temp1 - *temp2;
    }
}
bool isSorted(int *data, int size) {
    if (size < 3) {
        return true;
    }
    bool isBigger = false;
    bool isLess = false;
    for (int i = 0; i < size - 1; ++i) {
        if (data[i] > data[i + 1]) {
            isBigger = true;
        } else if (data[i] < data[i + 1]) {
            isLess = true;
        }
    }
    if (isBigger && isLess) {
        return false;
    }
    return true;
}

void monckeySort(int *data, int size) {
    int attempts = 0;
    while(!isSorted(data, size) && attempts < 1000) {
        mySwap(data + rand() % size, data + rand() % size);
        ++attempts;
    }
    return;
}

int sumOfDigits(int number) {
    int result = 0;
    number = (number < 0) ? -number : number;
    while (number != 0) {
        result = result + number % 10;
        number = number / 10;
    }
    return result;
}
void maxSum(int *array, int size, int *answer) {
    int maxSum = 0;
    int *result = (int *) malloc(sizeof(int) * 200);
    int index = 0;
    int bound = 0;
    for (int i = 0; i < size; ++i) {
        int sum = sumOfDigits(array[i]);
        if (sum > maxSum) {
            maxSum = sum;
            result[index] = array[i];
            bound = index;
            ++index;
        } else if (sum == maxSum) {
            result[index] = array[i];
            ++index;
        }
    }
    for (int i = bound; i < index; ++i) {
        answer[i - bound] = result[i];
    }
    answer[index - bound] = -1;
    free(result);
}

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

int frequency(int *data, int size, int *resultCharacters, int *frequencies) {
    int minimalValue = findMinValue(data, size);
    int maximalValue = findMaxValue(data, size);
    int * countArray = (int*) calloc(maximalValue - minimalValue + 1, sizeof(int));
    for (int i = 0; i < size; ++i) {
        countArray[data[i] - minimalValue] ++;
    }
    int index = 0;
    for (int i = 0; i < maximalValue - minimalValue + 1; ++i) {
        if (countArray[i] != 0) {
            resultCharacters[index] = i + minimalValue;
            frequencies[index] = countArray[i];
            ++index;
        }
    }
    free(countArray);
    return maximalValue - minimalValue + 1;
}

bool testFrequency(void) {
    char testingData[12] = {'a', 'b', 'c', '2', 'a', '*', 'a', 'a', 'g', 'S', 'Y', 'b'};
    int intData[12] = {0};
    for (int i = 0; i < 12; ++i) {
        intData[i] =(int) testingData[i];
    }
    int *resultCharacters = (int*) malloc(sizeof(int) * 10000);
    int *frequencies = (int*) malloc(sizeof(int) * 10000);
    frequency(intData, 12, resultCharacters, frequencies);
    int correctFrequency[8] = {1, 1, 1, 1, 4, 2, 1, 1};
    char correctSequence[8] = {'*', '2', 'S', 'Y', 'a', 'b', 'c', 'g'};
    for (int i = 0; i < 8; ++i) {
        if (frequencies[i] != correctFrequency[i]) {
            return false;
        }
        if ((char)resultCharacters[i] != correctSequence[i]) {
            return false;
        }
    }
    return true;
}

bool testSum(void) {
    int correctSequence[3] = {18, 45, 9};
    int testingData[5] = {18, 45, 13, 9, 17};
    int *result = (int *) malloc(sizeof(int) * 10);
    maxSum(testingData, 5, result);
    for (int i = 0; i < 3; ++i) {
        if (result[i] != correctSequence[i]) {
            free(result);
            return false;
        }
    }
    for (int i = 4; i < 5; ++i) {
        if (result[i] != 0) {
            free(result);
            return false;
        }
    }
    return true;
}

bool testMonckey(void) {
    int sequence[5] = {2, 5, 1, 7, 9};
    int answer1[5] = {9, 7, 5, 2, 1 };
    int answer2[5] = {1, 2, 5, 7, 9};
    monckeySort(sequence, 5);
    bool isEqual1 = true;
    bool isEqual2 = true;
    for (int i = 0; i < 5; ++i) {
        if (sequence[i] != answer1[i]) {
            isEqual1 = false;
        }
    }
    for (int i = 0; i < 5; ++i) {
        if (sequence[i] != answer2[i]) {
            isEqual2 = false;
        }
    }
    return (isEqual1 || isEqual2);
}

int main() {

    //1
    if (!testSum()) {
        printf("Test has been failed");
        return 1;
    } else {
        printf("Enter the size of the array:\n");
        int size = 0;
        scanf("%d", &size);
        printf("Enter the elements:\n");
        int *array = (int *) malloc(sizeof(int) * 1000);
        for (int i = 0; i < size; ++i) {
            scanf("%d", (array + i));
        }
        int *result = (int *) malloc(sizeof(int) * 1000);
        maxSum(array, size, result);
        printf("The numbers are:\n");
        for (int i = 0; i < 5; ++i) {
            if (result[i] == -1) {
                break;
            }
            printf("%d%s", result[i], " ");
        }
        printf("%s", "\n");
        free(result);
        free(array);
    }

    //2
    if (!testMonckey()) {
        printf("Test has been failed");
    } else {
        printf("Enter the size of the array:\n");
        int size = 0;
        scanf("%d", &size);
        printf("Enter the elements:\n");
        int *array = (int *) malloc(sizeof(int) * 1000);
        for (int i = 0; i < size; ++i) {
            scanf("%d", (array + i));
        }
        monckeySort(array, size);
        if (isSorted(array, size)) {
            for (int i = 0; i < size; ++i) {
                printf("%d%s", array[i], " ");
            }
        } else {
            printf("Not sorted\n");
        }
    }

    //3
    if (!testFrequency()) {
        printf("Test has been failed");
        return 1;
    } else {
        setlocale(LC_ALL, "RUS");
        FILE *file = fopen("../text", "r");
        if (file == NULL) {
            printf("%s", "file not found!");
            return 1;
        }
        int data[10000] = {0};
        int charactersRead = 0;
        unsigned char character = ' ';
        while (!feof(file)) {
            character = fgetc(file);
            data[charactersRead] = (int) character;
            ++charactersRead;
        }
        fclose(file);
        int *resultCharacters = (int*) malloc(sizeof(int) * 1000);
        int *frequencies = (int*) malloc(sizeof(int) * 1000);
        int size = frequency(data, charactersRead, resultCharacters, frequencies);
        for (int i = 0; i < size - 1; ++i) {
            if (frequencies[i] != 0) {
                printf("%c%s%d%s", (char)resultCharacters[i], " ", frequencies[i], "\n");
            }
        }
        free(resultCharacters);
        free(frequencies);
        return 0;
    }
}