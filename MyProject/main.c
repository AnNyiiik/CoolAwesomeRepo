#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrixFunctions.h"
#include "test.h"

int main() {
    if (!test()) {
        return 1;
    }
    FILE *file = fopen("../text", "r");
    Data *data = NULL;
    int error = readFromFile(file, &data);
    if (error == 1) {
        fclose(file);
        return 1;
    }
    fclose(file);
    int capitals = numberOfCapitals(data);
    List **countries = createCounties(data, &error);
    if (error == 1) {
        clearData(&data);
        return 1;
    }
    clearData(&data);
    for (int i = 0; i < capitals; ++i) {
        if (countries[i] != NULL) {
            printList(countries[i]);
        }
    }
    for (int i = 0; i < capitals; ++i) {
        deleteList(&countries[i]);
    }
    free(countries);
    return 0;
}
