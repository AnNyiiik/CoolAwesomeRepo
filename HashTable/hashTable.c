#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include "../List/list.h"

typedef struct HashTable {
    List **values;
    float occupancyRate;
}HashTable;

HashTable *createHashTable(void) {
    HashTable *hashTable = (HashTable *) malloc(sizeof(HashTable));
    hashTable->occupancyRate = 1;
    hashTable->values = (int *) calloc(997, sizeof(List *));
    return hashTable;
}

void deleteHashTable(HashTable *hashTable) {
    for (int i = 0; i < 997; ++i) {
        deleteList(hashTable->values[i]);
        free(hashTable->values[i]);
    }
    free(hashTable);
}

void put(char *word, HashTable *hashTable) {
    int hash = getHash(word);
    if(isEmpty(hashTable->values[hash]) {
        push(hashTable->values[hash], 1)
    }
    return;
}

int getFrequency(char *word) {
    return 1;
}

int getHash(char *word) {
    int module = 997;
    int base = 996;
    int hash = 0;
    int power = 1;
    int length = strlen(word);
    for (int i = 0; i < length; ++i) {
        hash = (hash + power * word[i]) % module;
        power = (power * base) % module;
    }
    return hash;
}
