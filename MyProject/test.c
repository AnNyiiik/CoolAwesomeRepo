#include "stdio.h"
#include "stdlib.h"
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
    int capitals = numberOfCapitals(data);
    List **countries = createCounties(data, &error);
    if (error == 1) {
        for (int i = 0; i < capitals; ++i) {
            deleteList(&countries[i]);
        }
        free(countries);
        return false;
    }
    int correctAnswers[9] = {4, 8, 1, 9, 7, 2, 5, 6, 3};
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