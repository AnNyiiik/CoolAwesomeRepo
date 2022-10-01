#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

void mySwap(int *temp1, int *temp2) {
    *temp1 = *temp1 + *temp2;
    *temp2 = *temp1 - *temp2;
    *temp1 = *temp1 - *temp2;
}

int countNullElements(const int *data, int size) {
    int answer = 0;

    for (int i = 0; i < size; ++i) {
        if (data[i] == 0) {
            ++answer;
        }
    }

    return answer;
}

int countLuckyBillets() {
    int sums[28];

    for (int i = 0; i < 28; ++i) {
        sums[i] = 0;
    }

    for (int i = 0; i < 10; ++i) {

        for (int j = 0; j < 10; ++j) {

            for (int k = 0; k < 10; ++k) {

                ++sums[i + j + k];
            }
        }
    }

    int answer = 0;

    for (int i = 0; i < 28; ++i) {

        answer += sums[i] * sums[i];
    }

    return answer;
}

int balanceOfBrackets(const char *string) {
    int counter = 0;

    for (int i = 0; string[i] != '\0'; ++i) {

        if (string[i] == ')') {
            --counter;

        } else if (string[i] == '(') {
            ++counter;
        }

        if (counter < 0) {
            return -1;
        }
    }

    return (counter > 0) ? 1 : 0;
}

void swapArrayOrder(int *array, int start, int end) {
    int index = 0;
    for (int i = start - 1; i < (end - start + 1) / 2 + start - 1; ++i) {
        int temp = array[i];
        array[i] = array[end - 1 - index];
        array[end - 1 - index] = temp;
        ++index;
    }
}

void allPrimeNumbers(int n, bool *numbers) {
    numbers[0] = false;
    numbers[1] = false;

    for (int i = 2; i < n + 1; ++i) {
        numbers[i] = true;
    }

    int divider = 2;

    while (divider * divider <= n) {

        if (numbers[divider]) {

            int index = divider * divider;

            while (index <= n) {
                numbers[index] = false;
                index += divider;
            }
        }

        ++divider;
    }
}

int remainderCounter(int number, int divider) {
    if (number == 0) {
        return 0;
    }

    if (divider == 0) {
        return INT32_MIN;
    }

    int sign = ((number < 0) && (divider > 0) || (number > 0) && (divider < 0)) ? -1 : 1;

    int numberAbs = abs(number);
    int dividerAbs = abs(divider);

    int remainder = 0;
    while (numberAbs >= dividerAbs) {
        numberAbs -= dividerAbs;
        ++remainder;
    }

    if (((remainder * dividerAbs) != abs(number)) && (number < 0)) {

        ++remainder;
    }

    return (sign < 0) ? -remainder : remainder;
}

int countSubstring(char const *string, char const *pattern) {
    unsigned int sizeOfString = strlen(string);
    unsigned int sizeOfPattern = strlen(pattern);
    int count = 0;

    for (unsigned int i = 0; i < sizeOfString - sizeOfPattern + 1; ++i) {
        int indexPattern = 0;
        int lengthCoincide = 0;
        for (unsigned int j = i; j < sizeOfPattern + i; ++j) {
            if (string[j] == pattern[indexPattern]) {
                ++lengthCoincide;
            } else {
                break;
            }
            ++indexPattern;
        }
        if (lengthCoincide == sizeOfPattern) {
            ++count;
        }
    }
    return count;
}

int main() {

    printf("%s", "Please, enter the number of the task:\n");
    int taskNumber = 0;
    scanf("%d", &taskNumber);

    if (taskNumber > 8 || taskNumber < 1) {

        printf("%s", "There is no such task, try again\n");

    }

    if (taskNumber == 1) {

        printf("%s", "Please, enter a and b:\n");

        int numberOne = 0;
        int numberTwo = 0;
        scanf("%d%d", &numberOne, &numberTwo);

        mySwap(&numberOne, &numberTwo);

        printf("%s%d%s%d%s", "a is ", numberOne, " and b is ", numberTwo, "\n");

    } else if (taskNumber == 2) {

        printf("%s", "Please, enter the size of the array:\n");

        int size = 0;
        scanf("%d", &size);

        int data[1000] = {0};

        printf("%s", "Please, enter the integer elements of the array:\n");

        for (int i = 0; i < size; ++i) {
            scanf("%d", &data[i]);
        }

        printf("%s%d%s", "There are ", countNullElements(data, size), " null elements\n");

    } else if (taskNumber == 3) {

        int dividedNumber = 0;
        int divider = 0;
        printf("%s", "Enter the divided number and divider:\n");
        scanf("%d%d", &dividedNumber, &divider);

        if (divider == 0) {

            printf("%s", "Your input is incorrect, divider = 0\n");

        } else {
            printf("%s%d", "The remainder is ", remainderCounter(dividedNumber, divider));
        }

    } else if (taskNumber == 4) {

        printf("%s%d", "The number of lucky billets is ", countLuckyBillets());

    } else if (taskNumber == 5) {

        char string[1000] = {' '};
        printf("%s", "Please, enter the sequence:\n");
        scanf("%s", string);

        int result = balanceOfBrackets(string);

        if (result == 0) {
            printf("%s", "The input was correct!\n");
        } else {
            printf("%s", "The input was incorrect :(\n");
        }

    } else if (taskNumber == 6) {

        int number = 0;

        printf("%s", "Please, enter the number:\n");
        scanf("%d", &number);

        bool numbers[10000] = {true};

        allPrimeNumbers(number, numbers);
        for (int i = 2; i <= number; ++i) {
            if (numbers[i]) {
                printf("%d%s", i, ", ");
            }
        }

    } else if (taskNumber == 7) {

        printf("%s", "Please, enter the string:\n");

        char const string[1000] = {' '};
        scanf("%s", string);

        printf("%s", "Please, enter the pattern:\n");

        char const pattern[1000] = {' '};
        scanf("%s", pattern);

        printf("%s%d", "The number of equal substrings is ", countSubstring(string, pattern));

    } else if (taskNumber == 8) {

        int size = 0;
        int bound = 0;

        printf("%s", "Please, enter the size of the array and the m-index:\n");
        scanf("%d%d", &size, &bound);

        if (bound > size) {
            printf("%s", "Your input is wrong, m-index cannot be more than the size of the array.\n");
        } else {

            int data[1000] = {0};

            printf("%s", "Please, enter the integer elements of the array:\n");

            for (int i = 0; i < size; ++i) {
                scanf("%d", &data[i]);
            }

            swapArrayOrder(data, 1, bound);
            swapArrayOrder(data, bound + 1, size);
            swapArrayOrder(data, 1, size);

            for (int i = 0; i < size; ++i) {
                printf("%d%s", data[i], " ");
            }
        }
    }
}










