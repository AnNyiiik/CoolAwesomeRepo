#ifndef MYPROJECT_MATRIXFUNCTIONS_H
#define MYPROJECT_MATRIXFUNCTIONS_H

#include <stdio.h>
#include "../List/list.h"

typedef struct Data Data;

// Return number of capitals;
int numberOfCapitals(Data *data);

// Clear data.
void clearData(Data **data);

// Read a data from file and fill in structure Data.
int readFromFile(FILE *file, Data **data);

// Create countries according to given data.
List  **createCounties(Data *data, int *error);

#endif //MYPROJECT_MATRIXFUNCTIONS_H
