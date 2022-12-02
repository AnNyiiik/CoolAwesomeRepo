#include "MatrixFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include "../List/list.h"
typedef struct Data Data;

typedef struct List {
    struct ListElement *head;
    int size;
} List;

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
    List **countries = (List **)calloc(data->numberOfCapitals, sizeof(List *));
    List **available = (List **)calloc(data->numberOfCapitals, sizeof(List *));
    int notDistributed = data->towns - data->numberOfCapitals;
    for (int i = 0; i < data->numberOfCapitals; ++i) {
        countries[i] = createList();
        push(&countries[i], data->capitals[i], 0);
        available[i] = createList();
        for (int j = 0; j < data->towns; ++j) {
            if (data->matrix[data->capitals[i] - 1][j] != 0) {
                push(&available[i], j + 1, data->matrix[data->capitals[i] - 1][j]);
            }
        }
    }
    while (notDistributed > 0) {
        for (int i = 0; i < data->numberOfCapitals; ++i) {
            if (notDistributed == 0) {
                break;
            }
            int town = 0;
            int path = 0;
            int errorCode = pop(&available[i], &town, &path);
            if (errorCode == 0) {
                for (int j = 0; j < data->towns; ++j) {
                    if (data->matrix[j][town - 1] != 0) {
                        if (getPath(countries[i], j + 1) != -1 && getPath(countries[i], j + 1) >
                                                                  path + data->matrix[j][town - 1]) {
                            delete(countries[i], getElementPlace(countries[i], j + 1));
                            push(&countries[i], j + 1, path + data->matrix[j][town - 1]);
                        } else if (getPath(countries[i], j + 1) == -1) {
                            push(&available[i], j + 1, path + data->matrix[j][town - 1]);
                        }
                    }
                }
                --notDistributed;
                push(&countries[i], town, path);
                for (int j = 0; j < data->numberOfCapitals; ++j) {
                    delete(available[j], getElementPlace(countries[j], town));
                }
            }
        }
    }
    for (int i = 0; i < data->numberOfCapitals; ++i) {
        printList(countries[i]);
    }
}