#include "kmp.h"

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

int countPattern(char const *path, char const *pattern, int *error) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        *error = 1;
        return -1;
    }
    char string[STR_SIZE] = {0};
    while(fgets(string, STR_SIZE, file) > 0) {
        int sizeString = strlen(string);
        int sizePattern = strlen(pattern);
        if (sizePattern > sizeString) {
            continue;
        }
        int sizeHelpString = sizeString + sizePattern;
        char *helpString = (char *)calloc(sizeHelpString, sizeof(char));
        if (helpString == NULL) {
            *error = 1;
            fclose(file);
            return -1;
        }
        strcpy(helpString, pattern);
        strcat(helpString, string);
        int *prefix = (int *)calloc(sizeHelpString + 1, sizeof(int));
        if (prefix == NULL) {
            free(helpString);
            *error = 1;
            fclose(file);
            return -1;
        }
        prefixFunction(helpString, sizeHelpString + 1, prefix);
        for (int i = 0; i < sizeHelpString + 1; ++i) {
            printf("%d ,", prefix[i]);
        }
        for (int i = 2 * sizePattern; i < sizeHelpString + 1; ++i) {
            if (prefix[i] >= sizePattern) {
                bool isEqual = true;
                if (i == 2 * sizePattern) {
                    for (int j = i - sizePattern; j < i; ++j) {
                        if (helpString[j] != helpString[j - sizePattern]) {
                            isEqual = false;
                            break;
                        }
                    }
                }
                if (!isEqual) {
                    continue;
                }
                free(prefix);
                free(helpString);
                fclose(file);
                return i - 2 * sizePattern;
            }
        }
        free(prefix);
        free(helpString);
    }
    fclose(file);
    return -1;
}