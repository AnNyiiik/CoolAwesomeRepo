#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrixFunctions.h"
#include "../List/list.h"
int main() {
    FILE *file = fopen("../text", "r");
    Data *data = NULL;
    readFromFile(file, &data);
    char *result = " ";
    createCounties(data, result);
    return 0;
}
