#ifndef MYPROJECT_MATRIXFUNCTIONS_H
#define MYPROJECT_MATRIXFUNCTIONS_H

#include <stdio.h>
#include "../List/list.h"

typedef struct Data {
    int roads;
    int towns;
    int **matrix;
    int *capitals;
    int numberOfCapitals;
} Data;

// Read a data from file and fill in structure Data.
int readFromFile(FILE *file, Data **data);

// Create countries according to given data.
int createCounties(Data *data, List ***result);

#endif //MYPROJECT_MATRIXFUNCTIONS_H
