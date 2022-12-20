#include "lexer.h"
#include "stdlib.h"
#include <string.h>

int **createTable(const char *path) {
    FILE *file = fopen(path, "r");
    int states = 0;
    fscanf(file, "%d", &states);
    int **table = (int **)calloc(states, sizeof(int *));
    int *possibleSteps = (int *)calloc(states, sizeof(int));
    for (int i = 0; i < states; ++i) {
        fscanf(file, "%d", &possibleSteps[i]);
        table[i] = (int *)calloc(possibleSteps[i], sizeof(int));
    }
    for (int i = 0; i < states; ++i) {
        for (int j = 0; j < possibleSteps[i]; ++j) {
            int from = 0;
            char symbol[10] = {0};
            int to = 0;
            fscanf(file, "%d%s%d", &from, symbol, &to);
            table[i][j] = to;
        }
    }
    fclose(file);
    return table;
}

int move(int from, char character, int **table) {
    if (character != '*' && character != '/') {
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

