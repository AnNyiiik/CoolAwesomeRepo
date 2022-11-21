#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashTable.h"
#include "../List/list.h"
#include "test.h"

int main() {
    if (!testCreateTable()) {
        return 1;
    }
    if (!testDelete()) {
        return 1;
    }
    if (!testHash()) {
        return 1;
    }
    if (!testAdd()) {
        return 1;
    }
    if (!testDelete()) {
        return 1;
    }
    if (!testResize()) {
        return 1;
    }
    if (!testMaxSegment()) {
        return 1;
    }
    if (!testAverageSegment()) {
        return 1;
    }
    if (!testOccupancy()) {
        return 1;
    }
    FILE *file = fopen("../text", "r");
    if (file == NULL) {
        printf("File not found");
        return 1;
    }
    int character = ' ';
    int length = 0;
    char *word = (char *)calloc(30, sizeof(char));
    HashTable *hashTable = createHashTable(INIT_SIZE);
    while ((character = fgetc(file)) != EOF) {
        if (character == ',' || character == '?' || character == '!' || character == ';' || character == '.'
        || character == ':' || character == '\"' || character == ' ' || character == '(' || character == ')' || character == '-') {
            if (length > 0) {
                resize(&hashTable);
                put(word, hashTable);
                free(word);
                word = (char *)calloc(30, sizeof(char));
                length = 0;
            }
        }else {
            word[length] = tolower(character);
            ++length;
        }
    }
    free(word);
    printTable(hashTable);
    printf("%f", occupancyRate(hashTable));
    deleteHashTable(&hashTable);
    return 0;
}
