#include "test.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>

bool test(void) {
    char *correctSequence[5] = {"/* hausiuh\n", "jsioaij */\n", "/*ajisoixjisoiqojjixosoiaj*/\n", "/**/\n", "/*/ aa*/\n"};
    int error = writeCommentsToFile("../output", "../testDataInput");
    if (error == 1) {
        return false;
    }
    FILE * file  = fopen("../output", "r");
    if (file == NULL) {
        return false;
    }
    int readLines = 0;
    char comment[COMMENT_SIZE] = {0};
    bool isSimilar = true;
    while(fgets(comment, COMMENT_SIZE, file) > 0) {
        if (strcmp(comment, correctSequence[readLines]) != 0) {
            isSimilar = false;
            break;
        }
        ++readLines;
    }
    fclose(file);
    return isSimilar && (readLines == 5);
}