#include "matrixFunctions.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct Data Data;

int readFromFile(FILE *file, Data **data) {
    if (file == NULL) {
        return 1;
    }
    Data *newData = (Data *)malloc(sizeof(Data));
    char *towns = (char *)malloc(10);
    fgets(towns, 10, file);
    newData->towns = atoi(towns);
    char *roads = (char *)malloc(10);
    fgets(roads, 10, file);
    newData->roads = atoi(roads);
    int **matrix = (int **)calloc(atoi(towns), sizeof(int *));
    for (int i = 0; i < atoi(towns); ++i) {
        matrix[i] = (int *)calloc(atoi(towns), sizeof(int));
    }
    for (int i = 0; i < atoi(roads); ++i) {
        int indexFirst = 0;
        int indexSecond = 0;
        int length = 0;
        char *string = (char *)malloc(sizeof(char) * 10);
        for (int j = 0; j < 3; ++j) {
            fscanf(file, "%s", string);
            if (j == 0) {
                indexFirst = atoi(string);
            } else if (j == 1) {
                indexSecond = atoi(string);
            } else {
                length = atoi(string);
            }
        }
        free(string);
        matrix[indexFirst - 1][indexSecond - 1] = length;
        matrix[indexSecond - 1][indexFirst - 1] = length;
    }
    newData->matrix = matrix;
    free(towns);
    free(roads);
    char *numberOfCapitals = (char*)malloc(sizeof(char) * 10);
    fscanf(file, "%s", numberOfCapitals);
    newData->numberOfCapitals = atoi(numberOfCapitals);
    int *capitals = (int *)calloc(newData->numberOfCapitals, sizeof(int));
    char *capital = NULL;
    for (int i = 0; i < atoi(numberOfCapitals); ++i) {
        capital = (char *)malloc(sizeof(char) * 10);
        fscanf(file, "%s", capital);
        capitals[i] = atoi(capital);
        free(capital);
    }
    newData->capitals = capitals;
    free(numberOfCapitals);
    (*data) = newData;
    return 0;
}

void createCounties(Data *data, char *result) {

}