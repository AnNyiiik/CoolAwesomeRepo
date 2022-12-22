#ifndef KMP_KMP_H
#define KMP_KMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STR_SIZE 100

// Find the first position of substring pattern in the given string. If there is no inclusion, return -1.
int findPositionInFile(char const *path, char const *pattern, int *error);

#endif //KMP_KMP_H
