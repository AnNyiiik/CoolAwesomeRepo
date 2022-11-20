#include "../List/list.h"
#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H
#define INIT_SIZE 8

typedef struct HashTable HashTable;

HashTable *createHashTable(int size);

void deleteHashTable(HashTable **hashTable);

void put(char *word, HashTable *hashTable);

void deleteWord(char *word, HashTable **hashTable);

int maxSegmentSize(HashTable *hashTable);

float occupancyRate(HashTable *hashTable);

int averageSegmentSize(HashTable *hashTable);

int getFrequency(char *word, HashTable *hashTable);

int getHash(char *word, int size);

void resize(HashTable **hashTable);

void printTable(HashTable *hashTable);

#endif //HASHTABLE_HASHTABLE_H
