#include <string.h>
#include <stdlib.h>
#include "test.h"
#include "hashTable.h"

bool testHash(void) {
    char *words[3] = {"fox", "snake", "yellow"};
    int hashes[3] = {7, 0, 4};
    for (int i = 0; i < 3; ++i) {
        int hash = getHash(words[i], INIT_SIZE);
        if (hash != hashes[i]) {
            return false;
        }
    }
    return true;
}

bool testOccupancy(void) {
    int error = 0;
    HashTable *hashTable = createHashTable(&error);
    if (error == 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    char *words[10] = {"fox", "apple", "snake", "mountain", "exquisite", "lengthy",
                       "capacity", "embroidery", "lake", "maple"};
    for (int i = 0; i < 10; ++i) {
        put(words[i % 10], hashTable, 1);
    }
    if (abs(occupancyRate(hashTable) - 1.25) > 0.001) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testMaxSegment(void) {
    int error = 0;
    HashTable *hashTable = createHashTable(&error);
    if (error == 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    char *words[10] = {"fox", "apple", "snake", "mountain", "exquisite",
                       "lengthy", "capacity", "embroidery", "lake", "maple"};
    for (int i = 0; i < 10; ++i) {
        put(words[i], hashTable, 1);
    }
    if (maxSegmentSize(hashTable) != 2) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testAverageSegment(void) {
    int error = 0;
    HashTable *hashTable = createHashTable(&error);
    if (error == 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    char *words[10] = {"fox", "apple", "snake", "mountain", "exquisite",
                       "lengthy", "capacity", "embroidery", "lake", "maple"};
    for (int i = 0; i < 10; ++i) {
        put(words[i], hashTable, 1);
        resize(&hashTable);
    }
    float average = averageSegmentSize(hashTable);
    if (abs(average - 1.1111) > 0.0001) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testAdd(void) {
    int error = 0;
    HashTable *hashTable = createHashTable(&error);
    if (error == 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    put("cloud", hashTable, 1);
    if (wordFrequency("cloud", hashTable) != 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testDelete(void) {
    int error = 0;
    HashTable *hashTable = createHashTable(&error);
    if (error == 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    put("cloud", hashTable, 1);
    deleteWord("cloud", &hashTable);
    if (wordFrequency("cloud", hashTable) != 0) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testCreateTable(void) {
    int error = 0;
    HashTable *hashTable = createHashTable(&error);
    if (error == 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    if (hashTable == NULL) {
        deleteHashTable(&hashTable);
        return false;
    }
    if (getNumberOfElements(hashTable) != 0 || getNumberOfUsedSegments(hashTable) != 0) {
        deleteHashTable(&hashTable);
        return false;
    }
    int capacity = size(hashTable);
    if (capacity != INIT_SIZE) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testDeleteTable(void) {
    int error = 0;
    HashTable *hashTable = createHashTable(&error);
    if (error == 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    if (hashTable != NULL) {
        return false;
    }
    return true;
}

bool testResize(void) {
    int error = 0;
    HashTable *hashTable = createHashTable(&error);
    if (error == 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    char *words[16] = {"rain", "rainbow", "maple", "green", "ocean", "mountain",
                       "roar", "storm", "goat", "lake", "tree", "cloud",
                       "bush", "stick", "dog", "cat"};
    for (int i = 0; i < 16; ++i) {
        put(words[i], hashTable, 1);
    }
    resize(&hashTable);
    if (size(hashTable) != INIT_SIZE * 2) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool test(void) {
    return testCreateTable() && testDelete() && testHash() && testAdd() && testDelete() &&
        testResize() && testMaxSegment() && testAverageSegment() && testOccupancy() && testDeleteTable();
}