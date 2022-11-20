#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashTable.h"
#include "../List/list.h"
#define INIT_SIZE 8

typedef struct HashTable {
    List **values;
    int size;
    int numberOfUsedSegments;
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

HashTable *createHashTable(int size) {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->numberOfUsedSegments = 0;
    hashTable->numberOfElements = 0;
    hashTable->values = (List**)calloc(size, sizeof(List *));
    for (int i = 0; i < size; ++i) {
        hashTable->values[i] = createList();
    }
    return hashTable;
}

void resize(HashTable **hashTable) {
    float occupancy = occupancyRate(*hashTable);
    if ((occupancy <= 1 && occupancy > 0.5) || (occupancy <= 0.5 && (*hashTable)->size == 8)) {
        return;
    }
    HashTable *newHashTable = NULL;
    if (occupancy > 1) {
        newHashTable = createHashTable((*hashTable)->size * 2);
    } else if (occupancy <= 0.5 && (*hashTable)->size > 8) {
        newHashTable = createHashTable((*hashTable)->size / 2);
    }
    for (int i = 0; i < (*hashTable)->size; ++i) {
        ListElement *element = (*hashTable)->values[i]->head;
        while (element != NULL) {
            put(element->word, newHashTable);
            element = element->next;
        }
    }
    deleteHashTable(&(*hashTable));
    (*hashTable) = newHashTable;
    return;
}

void deleteHashTable(HashTable **hashTable) {
    for (int i = 0; i < (*hashTable)->size; ++i) {
        deleteList(&((*hashTable)->values[i]));
        free((*hashTable)->values[i]);
    }
    free(*hashTable);
    *hashTable = NULL;
    return;
}

void deleteWord(char *word, HashTable **hashTable) {
    int hash = getHash(word, (*hashTable)->size);
    if (hash < 0 || hash >= (*hashTable)->size) {
        return;
    }
    if(isEmpty((*hashTable)->values[hash])) {
        return;
    }
    ListElement *element = (*hashTable)->values[hash]->head;
    while (element != NULL) {
        if (strcmp(element->word, word) == 0) {
            --(*hashTable)->numberOfElements;
            if (element->next == NULL) {
                --(*hashTable)->numberOfUsedSegments;
            }
            delete(word, &((*hashTable)->values[hash]));
            break;
        }
        element = element->next;
    }
    return;
}

void put(char *word, HashTable *hashTable) {
    int hash = getHash(word, hashTable->size);
    if (hash < 0 || hash >= hashTable->size) {
        return;
    }
    if (isEmpty(hashTable->values[hash])) {
        push(&(hashTable->values[hash]), 1, word);
        ++hashTable->numberOfElements;
        ++hashTable->numberOfUsedSegments;
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
            ++hashTable->numberOfElements;
            push(&(hashTable->values[hash]), 1, word);
        }
    }
    return;
}

int getFrequency(char *word, HashTable *hashTable) {
    int hash = getHash(word, hashTable->size);
    if (hash < 0 || hash >= hashTable->size) {
        return 1;
    }
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

void printTable(HashTable *hashTable) {
    for (int i = 0; i < hashTable->size; ++i) {
        if (hashTable->values[i]->head != NULL) {
            ListElement * element = hashTable->values[i]->head;
            while (element != NULL) {
                printf("%s%s%d%s", element->word, " - ", element->frequency, "\n");
                element = element->next;
            }
        }
    }
    return;
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
    return (float) hashTable->numberOfElements / hashTable->size;
}

int maxSegmentSize(HashTable *hashTable) {
    int max = hashTable->values[0]->size;
    for (int i = 1; i < hashTable->size; ++i) {
        if (hashTable->values[i]->size > max) {
            max = hashTable->values[i]->size;
        }
    }
    return max;
}

int averageSegmentSize(HashTable *hashTable) {
    return (hashTable->numberOfUsedSegments == 0) ? 1 : (int)(hashTable->numberOfElements/hashTable->numberOfUsedSegments);
}