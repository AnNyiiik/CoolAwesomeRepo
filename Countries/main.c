#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *file = fopen("../text", "r");
    if (file == NULL) {
        printf("file not found");
        return 1;
    }
    char *towns = (char *)malloc(10);
    fgets(towns, 10, file);
    char *roads = (char *)malloc(10);
    fgets(roads, 10, file);
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
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%d%s", matrix[i][j], " ");
        }
        printf("\n");
    }
    return 0;
}
