#include "stdio.h"
#include "test.h"
#include "MatrixFunctions.h"
#include "../List/list.h"

bool test(void) {
    FILE *file = fopen("../text", "r");
    Data *data = NULL;
    int error = readFromFile(file, &data);
    fclose(file);
    if (error == 1) {
        return false;
    }

    return 0;
}