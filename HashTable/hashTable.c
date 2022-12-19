#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include "../List/list.h"
#define INIT_SIZE 8

typedef struct HashTable {
    List **values;
    int size;
    int numberOfUsedSegments;
    int numberOfElements;
} HashTable;

int getNumberOfElements(HashTable *hashTable) {
    if (hashTable == NULL) {
        return 0;
    }
    return hashTable->numberOfElements;
}

int getNumberOfUsedSegments(HashTable *hashTable) {
    if (hashTable == NULL) {
        return 0;
    }
    return hashTable->numberOfUsedSegments;
}

int size(HashTable *hashTable) {
    if (hashTable == NULL) {
        return 0;
    }
    return hashTable->size;
}

HashTable *createHashTable(int size, int *error) {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    if (hashTable == NULL) {
        *error = 1;
        return NULL;
    }
    hashTable->size = size;
    hashTable->numberOfUsedSegments = 0;
    hashTable->numberOfElements = 0;
    hashTable->values = (List**)calloc(size, sizeof(List *));
    if (hashTable->values == NULL) {
        deleteHashTable(&hashTable);
        *error = 1;
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        hashTable->values[i] = createList(error);
        if (*error == 1) {
            for (int j = 0; j < i; ++j) {
                deleteList(&hashTable->values[j]);
            }
            free(hashTable->values);
            free(hashTable);
            return NULL;
        }
    }
    *error = 0;
    return hashTable;
}

int wordFrequency(char *word, HashTable *hashTable) {
    if (hashTable == NULL || hashTable->size == 0) {
        return 0;
    }
    int hash = getHash(word, hashTable->size);
    if (hash < 0) {
        hash = hashTable->size + hash;
    }
    int frequency = getFrequency(word, hashTable->values[hash]);
    if (frequency > 0) {
        return frequency;
    }
    return 0;
}

int resize(HashTable **hashTable) {
    if (hashTable == NULL || *hashTable == NULL || getNumberOfElements(*hashTable) == 0) {
        return 0;
    }
    float occupancy = occupancyRate(*hashTable);
    if ((occupancy <= 1 && occupancy > 0.5) || (occupancy <= 0.5 && (*hashTable)->size == 8)) {
        return 0;
    }
    HashTable *newHashTable = NULL;
    if (occupancy > 1) {
        int error = 0;
        newHashTable = createHashTable((*hashTable)->size * 2, &error);
        if (error == 1) {
            deleteHashTable(hashTable);
            return 1;
        }
    } else if (occupancy <= 0.5 && (*hashTable)->size > 8) {
        int error = 0;
        newHashTable = createHashTable((*hashTable)->size / 2, &error);
        if (error == 1) {
            deleteHashTable(hashTable);
            return 1;
        }
    }
    for (int i = 0; i < (*hashTable)->size; ++i) {
        while (!isEmpty((*hashTable)->values[i])) {
            char word[30] = {0};
            getHead((*hashTable)->values[i], word);
            put(word, newHashTable, getHeadFrequency((*hashTable)->values[i]));
            pop(&(*hashTable)->values[i]);
        }
    }
    deleteHashTable(&(*hashTable));
    *hashTable = newHashTable;
    return 0;
}

void deleteHashTable(HashTable **hashTable) {
    if (hashTable == NULL || *hashTable == NULL) {
        return;
    }
    for (int i = 0; i < (*hashTable)->size; ++i) {
        deleteList(&((*hashTable)->values[i]));
        free((*hashTable)->values[i]);
    }
    free(*hashTable);
    *hashTable = NULL;
}

void deleteWord(char *word, HashTable **hashTable) {
    if (hashTable == NULL || *hashTable == NULL || getNumberOfElements(*hashTable) == 0) {
        return;
    }
    int hash = getHash(word, (*hashTable)->size);
    if (hash < 0) {
        hash = (*hashTable)->size + hash;
    }
    if (isEmpty((*hashTable)->values[hash])) {
        return;
    }
    delete(word, &(*hashTable)->values[hash]);
}

void put(char *word, HashTable *hashTable, int frequency) {
    if (hashTable == NULL) {
        return;
    }
    int hash = getHash(word, hashTable->size);
    if (hash < 0) {
        hash = hashTable->size + hash;
    }
    if (isEmpty(hashTable->values[hash])) {
        push(&(hashTable->values[hash]), frequency, word);
        ++hashTable->numberOfElements;
        ++hashTable->numberOfUsedSegments;
    } else {
        bool isExists = false;
        tryAdd(&hashTable->values[hash], word, &isExists, frequency);
        if (!isExists) {
            ++hashTable->numberOfElements;
            push(&(hashTable->values[hash]), frequency, word);
        }
    }
}

void printTable(HashTable *hashTable) {
    if (hashTable == NULL || getNumberOfElements(hashTable) == 0) {
        return;
    }
    for (int i = 0; i < hashTable->size; ++i) {
        printList(hashTable->values[i]);
    }
}

int getHash(char *word, int size) {
    int module = size;
    int base = size - 1;
    int hash = 0;
    int power = 1;
    int length = strlen(word);
    for (int i = 0; i < length; ++i) {
        hash = (hash + power * word[i]) % module;
        power = (power * base) % module;
    }
    return hash;
}

float occupancyRate(HashTable *hashTable) {
    if (hashTable == NULL || getNumberOfElements(hashTable) == 0) {
        return 1;
    }
    if (hashTable->size != 0) {
        return (float) hashTable->numberOfElements / hashTable->size;
    } else {
        return 1;
    }
}

int maxSegmentSize(HashTable *hashTable) {
    if (hashTable == NULL || getNumberOfElements(hashTable) == 0) {
        return 0;
    }
    int max = getSize(hashTable->values[0]);
    for (int i = 1; i < hashTable->size; ++i) {
        int currentSize = getSize(hashTable->values[i]);
        if (currentSize > max) {
            max = currentSize;
        }
    }
    return max;
}

int averageSegmentSize(HashTable *hashTable) {
    if (hashTable == NULL ||  getNumberOfElements(hashTable) == 0) {
        return 0;
    }
    return (hashTable->numberOfUsedSegments == 0) ? 1 : (int)(hashTable->numberOfElements/hashTable->numberOfUsedSegments);
}