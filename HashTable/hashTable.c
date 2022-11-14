#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include "../List/list.h"

typedef struct HashTable {
    List *values[997];
    float occupancyRate;
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

HashTable *createHashTable(void) {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->occupancyRate = 1;
    for (int i = 0; i < 997; ++i) {
        hashTable->values[i] = createList();
    }
    return hashTable;
}

void deleteHashTable(HashTable **hashTable) {
    for (int i = 0; i < 997; ++i) {
        deleteList(&((*hashTable)->values[i]));
        free((*hashTable)->values[i]);
    }
    free(*hashTable);
    *hashTable = NULL;
    return;
}

void put(char *word, HashTable *hashTable) {
    int hash = getHash(word);
    if(isEmpty(hashTable->values[hash])) {
        push(&(hashTable->values[hash]), 1, word);
    } else {
        ListElement *element = hashTable->values[hash]->head;
        bool isExists = false;
        while (element != NULL) {
            if (strcmp(element->word, word) == 0) {
                ++hashTable->values[hash]->head->frequency;
                isExists = true;
                break;
            }
            element = element->next;
        }
        if (!isExists) {
            push(&(hashTable->values[hash]), 1, word);
        }
    }
    return;
}

int getFrequency(char *word, HashTable *hashTable) {
    int hash = getHash(word);
    if(isEmpty(hashTable->values[hash])) {
        return 0;
    } else {
        ListElement *element = hashTable->values[hash]->head;
        while (element != NULL) {
            if (strcmp(element->word, word) == 0) {
                return (hashTable->values[hash]->head->frequency);
            }
            element = element->next;
        }
    }
    return 0;
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
