#include "kmp.h"

int *prefixTable(char const *pattern, int *error) {
    int length = strlen(pattern);
    int *prefix = (int *)calloc(length, sizeof(int));
    if (prefix == NULL) {
        *error = 1;
        return NULL;
    }
    for (int i = 1; i < length; ++i) {
        int prefixValue = prefix[i - 1];
        while (pattern[prefixValue] != pattern[i] && prefixValue > 0) {
            prefixValue = prefix[prefixValue - 1];
        }
        if (pattern[prefixValue] == pattern[i]) {
            prefix[prefixValue] += 1;
        }
        prefix[i] = prefixValue;
    }
    return prefix;
}

int firstPosition(char const *string, char const *pattern, int *error) {
    *error = 0;
    int index = 0;
    int stringLength = strlen(string);
    int patternLength = strlen(pattern);
    int *prefix = prefixTable(pattern, error);
    if (*error == 1) {
        return  -1;
    }
    for (int i = 0; i < stringLength; ++i) {
        while (pattern[index] != string[i] && index > 0) {
            index = prefix[index - 1];
        }
        if (pattern[index] == string[i]) {
            index += 1;
        }
        if (index == patternLength) {
            free(prefix);
            return i - patternLength + 1;
        }
    }
    free(prefix);
    return -1;
}

int findPositionInFile(char const *path, char const *pattern, int *error) {
    *error = 0;
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        *error = 1;
        return -1;
    }
    char string[STR_SIZE] = {0};
    while (fscanf(file, "%s", string) > 0) {
        int position = firstPosition(string, pattern, error);
        if (*error == 1) {
            fclose(file);
            return -1;
        }
        if (position == -1) {
            continue;
        } else {
            *error = 0;
            fclose(file);
            return position;
        }
    }
    fclose(file);
    return -1;
}


