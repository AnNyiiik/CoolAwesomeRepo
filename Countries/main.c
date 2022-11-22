#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmake-build-debug/matrixFunctions.h"
int main() {
    FILE *file = fopen("../text", "r");
    Data *data = NULL;
    readFromFile(file, &data);
    for (int i = 0; i < 3; ++i) {
        printf("%d\n", data->capitals[i]);
    }
    return 0;
}
