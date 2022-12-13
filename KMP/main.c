#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//void prefix(char const *string, int *prefixes) {
//    int start = 0;
//    int end = 1;
//    while (end < strlen(string)) {
//        if (string[start] == string[end]) {
//            prefixes[end] = start + 1;
//            ++start;
//            ++end;
//        } else {
//            if (start == 0) {
//                prefixes[end] = 0;
//                ++end;
//            } else {
//                start = prefixes[start - 1];
//            }
//        }
//    }
//}

//void searchForCoincides(char const *string, char const *pattern, int const *prefixes, int *result) {
//    unsigned int i = 0;
//    unsigned int j = 0;
//    int position = 0;
//    while (i < strlen(string)) {
//        if (pattern[j] == string[i]) {
//            ++i;
//            ++j;
//            if (j == strlen(pattern)) {
//                result[position] = i - strlen(pattern);
//                ++position;
//                j = prefixes[j - 1];
//            }
//        } else {
//            if (j > 0) {
//                j = prefixes[j - 1];
//            } else {
//                ++i;
//            }
//        }
//    }
//}

int searchSubstring(char const *string, char const *pattern) {
    int module = 7;
    int base = 5;
    int hashPattern = 0;
    int patternLength = strlen(pattern);
    int stringLength = strlen(string);
    int stringHash = 0;
    int power = 1;
    int position = -1;
    for (int i = 0; i < patternLength - 1; ++i) {
        power = (power * base) % module;
    }
    for (int i = 0; i < patternLength; ++i) {
        hashPattern += (hashPattern * base + pattern[i]) % module;
        stringHash += (stringHash * base + string[i]) % module;
    }
    hashPattern = hashPattern % module;
    stringHash = stringHash % module;
    for (int i = 0; i <= stringLength - patternLength; ++i) {
        if (hashPattern == stringHash) {
            int stop = 0;
            for (int j = 0; j < patternLength; ++j) {
                if (string[i + j] != pattern[j]) {
                    stop = j;
                    break;
                }
                stop = j;
            }
            if (stop + 1 == patternLength) {
                position = i;
            }
        }
        if (i < stringLength - patternLength) {
            stringHash = (base * (stringHash - string[i] * power) + string[i + patternLength]) % module;
            if (stringHash < 0) {
                stringHash = stringHash + module;
            }
        }
    }
    return position;
}



int main() {
    int position = searchSubstring("ababbaba", "aba");
    printf("%d", position);
//    char const *string = "ababbaba";
//    char const *substring = "aba";
//    int *prefixes = (int *)calloc(strlen(substring), sizeof(int));
//    prefix(substring, prefixes);
//    int *result = (int *)calloc(strlen(string), sizeof(int));
//    searchForCoincides(string, substring, prefixes, result);
//    for (int i = 0; i < strlen(string); ++ i) {
//        printf("%d%s", result[i], " ");
//    }
//    free(result);
//    free(prefixes);
}

