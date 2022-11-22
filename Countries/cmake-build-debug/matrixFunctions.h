#include <stdio.h>
#ifndef COUNTRIES_MATRIXFUNCTIONS_H
#define COUNTRIES_MATRIXFUNCTIONS_H
typedef struct Data {
    int roads;
    int towns;
    int **matrix;
    int *capitals;
    int numberOfCapitals;
} Data;
int readFromFile(FILE *file, Data **data);
#endif //COUNTRIES_MATRIXFUNCTIONS_H
