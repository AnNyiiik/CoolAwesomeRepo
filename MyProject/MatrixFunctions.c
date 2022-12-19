#include "MatrixFunctions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Data Data;

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
    char towns[10] = {0};
    fgets(towns, 10, file);
    newData->towns = atoi(towns);
    char roads[10] = {0};
    fgets(roads, 10, file);
    newData->roads = atoi(roads);
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
        char string[10] = {0};
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
        matrix[indexFirst - 1][indexSecond - 1] = length;
        matrix[indexSecond - 1][indexFirst - 1] = length;
    }
    newData->matrix = matrix;
    char numberOfCapitals[10] = {0};
    fscanf(file, "%s", numberOfCapitals);
    newData->numberOfCapitals = atoi(numberOfCapitals);
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
        char capital[10] = {0};
        fscanf(file, "%s", capital);
        capitals[i] = atoi(capital);
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

int createCounties(Data *data, List ***result) {
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
        int error = 0;
        countries[i] = createList(&error);
        error = push(&countries[i], data->capitals[i], 0);
        if (error == 1) {
            deleteData(countries, available, isFree, data->numberOfCapitals);
            return 1;
        }
        available[i] = createList(&error);
        if (error == 1) {
            deleteData(countries, available, isFree, data->numberOfCapitals);
            return 1;
        }
        for (int j = 0; j < data->towns; ++j) {
            if (data->matrix[data->capitals[i] - 1][j] != INT32_MAX) {
                error = insertByOrder(available[i], j + 1, data->matrix[data->capitals[i] - 1][j]);
                if (error == 1) {
                    deleteData(countries, available, isFree, data->numberOfCapitals);
                    return 1;
                }
            }
        }
        for (int j = 0; j < data->numberOfCapitals; ++j) {
            if (getElementPlace(available[i], data->capitals[i]) != -1) {
                error = delete(available[i], getElementPlace(available[i], data->capitals[i]));
                if (error == 1) {
                    deleteData(countries, available, isFree, data->numberOfCapitals);
                    return 1;
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
            int errorCode = pop(&available[i], &town, &path);
            if (errorCode != 0) {
                deleteData(countries, available, isFree, data->numberOfCapitals);
                return 1;
            }
            for (int j = 0; j < data->towns; ++j) {
                if (data->matrix[j][town - 1] != INT32_MAX) {
                    int dist = getPath(countries[i], j + 1);
                    if (dist != -1 && getPath(countries[i], j + 1) >
                                                              path + data->matrix[j][town - 1]) {
                        errorCode = delete(countries[i], getElementPlace(countries[i], j + 1));
                        if (errorCode == 1) {
                            deleteData(countries, available, isFree, data->numberOfCapitals);
                            return 1;
                        }
                        errorCode = push(&countries[i], j + 1, path + data->matrix[j][town - 1]);
                        if (errorCode == 1) {
                            deleteData(countries, available, isFree, data->numberOfCapitals);
                            return 1;
                        }
                    } else if (isFree[j] && getPath(countries[i], j + 1) == -1) {
                            errorCode = insertByOrder(available[i], j + 1, path + data->matrix[j][town - 1]);
                        if (errorCode == 1) {
                            deleteData(countries, available, isFree, data->numberOfCapitals);
                            return 1;
                        }
                    }
                }
            }
            --notDistributed;
            isFree[town - 1] = false;
            errorCode = push(&countries[i], town, path);
            if (errorCode == 1) {
                deleteData(countries, available, isFree, data->numberOfCapitals);
                return 1;
            }
            for (int j = 0; j < data->numberOfCapitals; ++j) {
                if (j == (data->capitals[i] - 1)) {
                    continue;
                }
                if (getElementPlace(available[j], town) != -1) {
                    errorCode = delete(available[j], getElementPlace(available[j], town));
                    if (errorCode == 1) {
                        deleteData(countries, available, isFree, data->numberOfCapitals);
                        return 1;
                    }
                }
            }
        }
    }
    if (notDistributed == 0) {
        int numberOfCapitals = data->numberOfCapitals;
        clearData(&data);
        for (int i = 0; i < numberOfCapitals; ++i) {
            *result[i] = countries[i];
        }
        for (int j = 0; j < numberOfCapitals; ++j) {
            deleteList(&available[j]);
        }
        free(available);
        free(isFree);
        return 0;
    }
}