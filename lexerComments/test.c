#include "test.h"

bool test(void) {
    char *correctSequence[3] = {"/*Hi*/\n", "/*, amogus*/\n", "/*ajisoixjisoiqojjixosoiaj*/\n"};
    writeCommentsToFile("../output", "../testDataInput");
    FILE * file  = fopen("../output", "r");
    int readLines = 0;
    char comment[100] = {0};
    bool isSimilar = true;
    while(fgets(comment, 100, file) > 0) {
        if (strcmp(comment, correctSequence[readLines]) != 0) {
            isSimilar = false;
            break;
        }
        ++readLines;
    }
    fclose(file);
    return isSimilar && (readLines == 3);
}