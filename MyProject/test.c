#include "stdio.h"
#include "stdlib.h"
#include "test.h"
#include "MatrixFunctions.h"

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
    bool result = true;
    int j = 0;
    for (int i = 0; i < capitals; ++i) {
        if (countries[i] != NULL) {
            while (!isEmpty(countries[i])) {
                int town = 0;
                int path = 0;
                error = pop(&countries[i], &town, &path);
                if (error == 1) {
                    result = false;
                    break;
                }
                if (town != correctAnswers[j]) {
                    result = false;
                    break;
                }
                ++j;
            }
            if (!result) {
                break;
            }
        }
    }
    for (int i = 0; i < capitals; ++i) {
        deleteList(&countries[i]);
    }
    free(countries);
    return result;
}