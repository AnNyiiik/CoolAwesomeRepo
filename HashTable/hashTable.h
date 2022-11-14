#include "../List/list.h"
#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

typedef struct HashTable HashTable;

HashTable *createHashTable(void);

void deleteHashTable(HashTable **hashTable);

void put(char *word, HashTable *hashTable);

void deleteWord(char *word, HashTable **hashTable);

int maxSegmentSize(HashTable *hashTable);

int occupancyRate(HashTable *hashTable);

int getFrequency(char *word, HashTable *hashTable);

int getHash(char *word);

#endif //HASHTABLE_HASHTABLE_H
