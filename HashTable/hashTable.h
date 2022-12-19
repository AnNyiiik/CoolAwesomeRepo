#include "../List/list.h"
#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#define INIT_SIZE 8
#define STR_SIZE 30

typedef struct HashTable HashTable;

// Create an empty hashTable.
HashTable *createHashTable(int size, int *error);

// Delete a hash table.
void deleteHashTable(HashTable **hashTable);

// Put a word into a table.
void put(char *word, HashTable *hashTable, int frequency);

// Delete a word from a table.
void deleteWord(char *word, HashTable **hashTable);

// Return the biggest size of all segments.
int maxSegmentSize(HashTable *hashTable);

// Return an occupancyRate.
float occupancyRate(HashTable *hashTable);

// Return an average segment size.
int averageSegmentSize(HashTable *hashTable);

// Count a hash for the word.
int getHash(char *word, int size);

// Resize the hash table according to occupancyRate.
int resize(HashTable **hashTable);

// Return a frequency of a given word.
int wordFrequency(char *word, HashTable *hashTable);

// Print hash table.
void printTable(HashTable *hashTable);

// Return the number of elements in the table.
int getNumberOfElements(HashTable *hashTable);

// Return the number of segments in the table.
int getNumberOfUsedSegments(HashTable *hashTable);

// Return the size of the table.
int size(HashTable *hashTable);

#endif //HASHTABLE_HASHTABLE_H
