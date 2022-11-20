#include <string.h>
#include <stdlib.h>
#include "test.h"
#include "hashTable.h"

typedef struct HashTable {
    List **values;
    int size;
    int numberOfSegments;
    int numberOfElements;
} HashTable;

typedef struct ListElement {
    int frequency;
    char *word;
    struct ListElement *next;
} ListElement;

typedef struct List {
    struct ListElement *head;
    struct ListElement *tail;
    int size;
} List;

bool testHash(void) {
    char *words[3] = {"fox", "snake", "yellow"};
    int hashes[3] = {111, 96, 12};
    for (int i = 0; i < 3; ++i) {
        int hash = getHash(words[i], 8);
        if (hash != hashes[i]) {
            return false;
        }
    }
    return true;
}

bool testOccupancy(void) {
    HashTable *hashTable = createHashTable(INIT_SIZE);
    char *words[10] = {"fox", "apple", "snake", "mountain", "exquisite", "lengthy", "capacity", "embroidery", "lake", "maple"};
    for (int i = 0; i < 1000; ++i) {
        put(words[i % 10], hashTable);
    }
    if (abs(occupancyRate(hashTable) - 0.01) > 0.001) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testMaxSegment(void) {
    HashTable *hashTable = createHashTable(INIT_SIZE);
    char *words[10] = {"fox", "apple", "snake", "mountain", "exquisite", "lengthy", "capacity", "embroidery", "lake", "maple"};
    for (int i = 0; i < 1000; ++i) {
        put(words[i % 10], hashTable);
    }
    if (maxSegmentSize(hashTable) != 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testAverageSegment(void) {
    HashTable *hashTable = createHashTable(INIT_SIZE);
    char *words[10] = {"fox", "apple", "snake", "mountain", "exquisite", "lengthy", "capacity", "embroidery", "lake", "maple"};
    for (int i = 0; i < 1000; ++i) {
        put(words[i % 10], hashTable);
    }
    if (averageSegmentSize(hashTable) != 1) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testAdd(void) {
    HashTable *hashTable = createHashTable(INIT_SIZE);
    int hash = getHash("cloud", 8);
    put("cloud", hashTable);
    if (strcmp(hashTable->values[hash]->head->word, "cloud") != 0) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testDelete(void) {
    HashTable *hashTable = createHashTable(INIT_SIZE);
    int hash = getHash("cloud", 8);
    put("cloud", hashTable);
    deleteWord("cloud", &hashTable);
    if (hashTable->values[hash]->head != NULL) {
        deleteHashTable(&hashTable);
        return false;
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testCreateTable(void) {
    HashTable *hashTable = createHashTable(INIT_SIZE);
    if (hashTable == NULL) {
        deleteHashTable(&hashTable);
        return false;
    }
    if (hashTable->numberOfElements != 0 || hashTable->numberOfSegments != 0) {
        deleteHashTable(&hashTable);
        return false;
    }
    for (int i = 0; i < hashTable->size; ++i) {
        if (hashTable->values[i] == NULL) {
            deleteHashTable(&hashTable);
            return false;
        }
    }
    deleteHashTable(&hashTable);
    return true;
}

bool testDeleteTable(void) {
    HashTable *hashTable = createHashTable(INIT_SIZE);
    deleteHashTable(&hashTable);
    if (hashTable != NULL) {
        return false;
    }
    return true;
}