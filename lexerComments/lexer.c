#include "lexer.h"
#include "stdlib.h"
#include <string.h>

int **createTable(const char *path) {
    FILE *file = fopen(path, "r");
    int states = 0;
    fscanf(file, "%d", &states);
    int **table = (int **)calloc(states, sizeof(int *));
    for (int i = 0; i < states; ++i) {
        table[i] = (int *)calloc(3, sizeof(int));
    }
    char string[10] = {0};
    for (int i = 0; i < states; ++i) {
        fscanf(file, "%s", string);
    }
    for (int i = 0; i < states; ++i) {
        fscanf(file, "%s", string);
        for (int j = 0; j < 3; ++j) {
            int state = 0;
            fscanf(file, "%d", &state);
            table[i][j] = state;
        }
    }
    fclose(file);
    return table;
}

int move(int from, char character, int **table) {
    if (character != '*' && character != '/') {
        return table[from][2];
    } else if (character == '/') {
        return table[from][0];
    }
    return table[from][1];
}

int writeCommentsToFile(char const *outputFile, char const *inputFile) {
    FILE *input = fopen(inputFile, "r");
    if (input == NULL) {
        return 1;
    }
    FILE *output = fopen(outputFile, "w");
    if (output == NULL) {
        return 1;
    }
    int **table = createTable("../table");
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    int state = 0;
    char *comment = (char *)calloc(100, sizeof(char));
    comment[0] = '/';
    comment[1] = '*';
    int character = 0;
    int position = 2;
    while ((character = fgetc(input)) > 0) {
        if (state == 2 || state == 3) {
            comment[position] = (char)character;
            ++position;
        }
        state = move(state, (char)character, table);
        if (state == 0 && strcmp(comment, "/*") != 0) {
            fprintf(output, "%s", comment);
            fprintf(output, "\n");
            free(comment);
            comment = (char *)calloc(100, sizeof(char));
            comment[0] = '/';
            comment[1] = '*';
            position = 2;
        }
    }
    fclose(output);
    fclose(input);
}

