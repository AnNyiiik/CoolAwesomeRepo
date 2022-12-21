#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hashTable.h"
#include "../List/list.h"
#include "test.h"

int main() {
    if (!test()) {
        return 1;
    }
    FILE *file = fopen("../text", "r");
    if (file == NULL) {
        printf("File not found");
        return 1;
    }
    char word[STR_SIZE] = {0};
    int error = 0;
    HashTable *hashTable = createHashTable(&error);
    if (error == 1) {
        fclose(file);
        deleteHashTable(&hashTable);
        return 1;
    }
    while (fscanf(file, "%s", word) > 0) {
        int length = strlen(word);
        for (int i = 0; i < length; ++i) {
            word[i] = tolower(word[i]);
        }
        if (length == 1 && (word[0] > 122 || word[0] < 97)) {
            continue;
        }
        if (word[length - 1] == '.' || word[length - 1] == ',' || word[length - 1] == '?' || word[length - 1] == '!' ||
                word[length - 1] == ':' || word[length - 1] == ';') {
            word[length - 1] = '\0';
        }
        put(word, hashTable, 1);
        error = resize(&hashTable);
        if (error == 1) {
            fclose(file);
            deleteHashTable(&hashTable);
            return 1;
        }
    }
    fclose(file);
    printTable(hashTable);
    printf("occupancy : %f\n", occupancyRate(hashTable));
    printf("max segment size : %d\n", maxSegmentSize(hashTable));
    printf("average segment size : %f\n", averageSegmentSize(hashTable));
    deleteHashTable(&hashTable);
    return 0;
}
