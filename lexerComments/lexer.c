#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"

int **createTable(const char *path, int *states, int *error) {
    *error = 0;
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        *error = 1;
        return NULL;
    }
    *states = 0;
    fscanf(file, "%d", states);
    int **table = (int **)calloc(*states, sizeof(int *));
    if (table == NULL) {
        *error = 1;
        fclose(file);
        return NULL;
    }
    for (int i = 0; i < *states; ++i) {
        table[i] = (int *)calloc(3, sizeof(int));
        if (table[i] == NULL) {
            *error = 1;
            for (int j = 0; j < i; ++j) {
                free(table[i]);
            }
            free(table);
            fclose(file);
            return NULL;
        }
    }
    for (int i = 0; i < *states; ++i) {
        fscanf(file, "%*s");
    }
    for (int i = 0; i < *states; ++i) {
        fscanf(file, "%*s");
        for (int j = 0; j < 3; ++j) {
            fscanf(file, "%d", &table[i][j]);
        }
    }
    fclose(file);
    return table;
}

void deleteTable(int **table, int rows) {
    if (table == NULL) {
        return;
    }
    for (int i = 0; i < rows; ++i) {
        if (table[i] != NULL) {
            free(table[i]);
        }
    }
    free(table);
}

int getCharacterClass(char character) {
    if (character != '*' && character != '/') {
        return 2;
    }
    return (character == '/') ? 0 : 1;
}

int move(int from, int characterClass, int **table) {
    return table[from][characterClass];
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
    int error = 0;
    int states = 0;
    int **table = createTable("../table", &states, &error);
    int currentState = 0;
    char *comment = (char *)calloc(COMMENT_SIZE, sizeof(char));
    if (comment == NULL) {
        deleteTable(table, states);
        fclose(input);
        fclose(output);
        return 1;
    }
    comment[0] = '/';
    comment[1] = '*';
    int character = 0;
    int position = 2;
    while ((character = fgetc(input)) > 0) {
        if (currentState == 2 || currentState == 3) {
            comment[position] = (char)character;
            ++position;
        }
        int characterClass = getCharacterClass(character);
        currentState = move(currentState, characterClass, table);
        if (currentState == 0 && strcmp(comment, "/*") != 0) {
            fprintf(output, "%s", comment);
            fprintf(output, "\n");
            free(comment);
            comment = (char *)calloc(COMMENT_SIZE, sizeof(char));
            if (comment == NULL) {
                deleteTable(table, states);
                fclose(input);
                fclose(output);
                return 1;
            }
            comment[0] = '/';
            comment[1] = '*';
            position = 2;
        }
    }
    deleteTable(table, states);
    free(comment);
    fclose(output);
    fclose(input);
    return 0;
}

