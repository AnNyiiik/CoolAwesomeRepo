#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrixFunctions.h"

int main() {
    FILE *file = fopen("../text", "r");
    Data *data = NULL;
    int error = readFromFile(file, &data);
    if (error == 1) {
        fclose(file);
        return 1;
    }
    fclose(file);
    int numberOfCapitals = data->numberOfCapitals;
    List **countries = createCounties(data, &error);
    for (int i = 0; i < numberOfCapitals; ++i) {
        if (countries[i] != NULL) {
            printList(countries[i]);
        }
    }
    for (int i = 0; i < numberOfCapitals; ++i) {
        deleteList(&countries[i]);
    }
    free(countries);
    return 0;
}
