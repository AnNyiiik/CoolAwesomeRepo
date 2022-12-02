#ifndef MYPROJECT_MATRIXFUNCTIONS_H
#define MYPROJECT_MATRIXFUNCTIONS_H

#include <stdio.h>

typedef struct Data {
    int roads;
    int towns;
    int **matrix;
    int *capitals;
    int numberOfCapitals;
} Data;
int readFromFile(FILE *file, Data **data);

void createCounties(Data *data, char *result);

#endif //MYPROJECT_MATRIXFUNCTIONS_H
