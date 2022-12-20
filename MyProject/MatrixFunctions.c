#include "MatrixFunctions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Data {
    int roads;
    int towns;
    int **matrix;
    int *capitals;
    int numberOfCapitals;
} Data;

int numberOfCapitals(Data *data) {
    if (data == NULL) {
        return -1;
    }
    return data->numberOfCapitals;
}

void clearData(Data **data) {
    for (int i = 0; i < (*data)->towns; ++i) {
        free((*data)->matrix[i]);
    }
    free((*data)->matrix);
    free((*data)->capitals);
    free((*data));
    (*data) = NULL;
}

int readFromFile(FILE *file, Data **data) {
    if (file == NULL) {
        return 1;
    }
    Data *newData = (Data *)malloc(sizeof(Data));
    if (newData == NULL) {
        return 1;
    }
    int towns = 0;
    fscanf(file, "%d", &towns);
    newData->towns = towns;
    int roads = 0;
    fscanf(file, "%d", &roads);
    newData->roads = roads;
    int **matrix = (int **)calloc(newData->towns, sizeof(int *));
    if (matrix == NULL) {
        free(newData);
        return 1;
    }
    for (int i = 0; i < newData->towns; ++i) {
        matrix[i] = (int *)calloc(newData->towns, sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(matrix[j]);
            }
            free(newData);
            free(matrix);
            return 1;
        }
    }
    for (int i = 0 ; i < newData->towns; ++i) {
        for (int j = 0; j < newData->towns; ++j) {
            matrix[i][j] = INT32_MAX;
        }
    }
    for (int i = 0; i < newData->roads; ++i) {
        int indexFirst = 0;
        int indexSecond = 0;
        int length = 0;
        int number = 0;
        for (int j = 0; j < 3; ++j) {
            fscanf(file, "%d", &number);
            if (j == 0) {
                indexFirst = number;
            } else if (j == 1) {
                indexSecond = number;
            } else {
                length = number;
            }
        }
        matrix[indexFirst - 1][indexSecond - 1] = length;
        matrix[indexSecond - 1][indexFirst - 1] = length;
    }
    newData->matrix = matrix;
    int numberOfCapitals = 0;
    fscanf(file, "%d", &numberOfCapitals);
    newData->numberOfCapitals = numberOfCapitals;
    int *capitals = (int *)calloc(newData->numberOfCapitals, sizeof(int));
    if (capitals == NULL) {
        for (int j = 0; j < newData->numberOfCapitals; ++j) {
            free(matrix[j]);
        }
        free(newData);
        free(matrix);
        return 1;
    }
    for (int i = 0; i < newData->numberOfCapitals; ++i) {
        int capital = 0;
        fscanf(file, "%d", &capital);
        capitals[i] = capital;
    }
    newData->capitals = capitals;
    *data = newData;
    return 0;
}

void deleteData(List **countries, List **available, bool *isFree, int numberOfCapitals) {
    for (int j = 0; j < numberOfCapitals; ++j) {
        deleteList(&countries[j]);
        deleteList(&available[j]);
    }
    free(countries);
    free(available);
    free(isFree);
}

List  **createCounties(Data *data, int *error) {
    List **countries = (List **)calloc(data->numberOfCapitals, sizeof(List *));
    List **available = (List **)calloc(data->numberOfCapitals, sizeof(List *));
    bool *isFree = (bool*)calloc(data->towns, sizeof(bool));
    for (int i = 0; i < data->towns; ++i) {
        isFree[i] = true;
    }
    for (int i = 0; i < data->numberOfCapitals; ++i) {
        isFree[data->capitals[i] - 1] = false;
    }
    int notDistributed = data->towns - data->numberOfCapitals;
    for (int i = 0; i < data->numberOfCapitals; ++i) {
        countries[i] = createList(error);
        *error = push(&countries[i], data->capitals[i], 0);
        if (*error == 1) {
            deleteData(countries, available, isFree, data->numberOfCapitals);
            return NULL;
        }
        available[i] = createList(error);
        if (*error == 1) {
            deleteData(countries, available, isFree, data->numberOfCapitals);
            return NULL;
        }
        for (int j = 0; j < data->towns; ++j) {
            if (data->matrix[data->capitals[i] - 1][j] != INT32_MAX) {
                *error = insertByOrder(available[i], j + 1, data->matrix[data->capitals[i] - 1][j]);
                if (*error == 1) {
                    deleteData(countries, available, isFree, data->numberOfCapitals);
                    return NULL;
                }
            }
        }
        for (int j = 0; j < data->numberOfCapitals; ++j) {
            if (getElementPlace(available[i], data->capitals[i]) != -1) {
                *error = delete(available[i], getElementPlace(available[i], data->capitals[i]));
                if (*error == 1) {
                    deleteData(countries, available, isFree, data->numberOfCapitals);
                    return NULL;
                }
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
            if (isEmpty(available[i])) {
                continue;
            }
            *error = pop(&available[i], &town, &path);
            if (*error != 0) {
                deleteData(countries, available, isFree, data->numberOfCapitals);
                return NULL;
            }
            for (int j = 0; j < data->towns; ++j) {
                if (data->matrix[j][town - 1] != INT32_MAX) {
                    int dist = getPath(countries[i], j + 1);
                    if (dist != -1 && dist > path + data->matrix[j][town - 1]) {
                        *error = delete(countries[i], getElementPlace(countries[i], j + 1));
                        if (*error == 1) {
                            deleteData(countries, available, isFree, data->numberOfCapitals);
                            return NULL;
                        }
                        *error = push(&countries[i], j + 1, path + data->matrix[j][town - 1]);
                        if (*error == 1) {
                            deleteData(countries, available, isFree, data->numberOfCapitals);
                            return NULL;
                        }
                    } else if (isFree[j] && getPath(countries[i], j + 1) == -1) {
                            *error = insertByOrder(available[i], j + 1, path + data->matrix[j][town - 1]);
                        if (*error == 1) {
                            deleteData(countries, available, isFree, data->numberOfCapitals);
                            return NULL;
                        }
                    }
                }
            }
            --notDistributed;
            isFree[town - 1] = false;
            *error = push(&countries[i], town, path);
            if (*error == 1) {
                deleteData(countries, available, isFree, data->numberOfCapitals);
                return NULL;
            }
            for (int j = 0; j < data->numberOfCapitals; ++j) {
                if (j == (data->capitals[i] - 1)) {
                    continue;
                }
                if (getElementPlace(available[j], town) != -1) {
                    *error = delete(available[j], getElementPlace(available[j], town));
                    if (*error == 1) {
                        deleteData(countries, available, isFree, data->numberOfCapitals);
                        return NULL;
                    }
                }
            }
        }
    }
    int capitals = numberOfCapitals(data);
    for (int j = 0; j < capitals; ++j) {
        deleteList(&available[j]);
    }
    free(available);
    free(isFree);
    return countries;
}