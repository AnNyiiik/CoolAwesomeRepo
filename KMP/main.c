#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prefixFunction(char const *string, int size, int *prefix) {
    prefix[0] = -1;
    for (int i = 1; i <= size; ++i) {
        int length = prefix[i - 1];
        while (length != -1 && string[length] != string[i - 1]) {
            length = prefix[length];
        }
        prefix[i] = length + 1;
    }
}

int countPattern(char const *string, char const *pattern) {
    int sizeString = strlen(string);
    int sizePattern = strlen(pattern);
    if (sizePattern > sizeString) {
        return -1;
    }
    int sizeHelpString = sizeString + sizePattern + 1;
    char *helpString = (char *)calloc(sizeHelpString, sizeof(char));
    strcpy(helpString, pattern);
    strcat(helpString, string);
    int *prefix = (int *)calloc(sizeHelpString + 1, sizeof(int));
    prefixFunction(helpString, sizeHelpString + 1, prefix);
    for (int i = sizePattern; i < sizeHelpString; ++i) {
        if (prefix[i] == sizePattern) {
            free(prefix);
            free(helpString);
            return i - 2 * sizePattern;
        }
    }
    free(prefix);
    free(helpString);
    return -1;
}

int main() {
    int answer = countPattern("ababbaba", "aba");
    printf("%d", answer);
}

