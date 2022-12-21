#ifndef KMP_KMP_H
#define KMP_KMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STR_SIZE 100

// Count the amount of inclusions of pattern in the string.
int countPattern(char const *string, char const *pattern, int *error);

#endif //KMP_KMP_H
