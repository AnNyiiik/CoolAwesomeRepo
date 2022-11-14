#include <stdlib.h>
#include <string.h>
#include "hashTable.h"
#include "../List/list.h"

typedef struct HashTable {
    List *values[997];
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

HashTable *createHashTable(void) {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->numberOfSegments = 0;
    hashTable->numberOfElements = 0;
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

void deleteWord(char *word, HashTable **hashTable) {
    int hash = getHash(word);
    if(isEmpty((*hashTable)->values[hash])) {
        return;
    }
    ListElement *element = (*hashTable)->values[hash]->head;
    while (element != NULL) {
        if (strcmp(element->word, word) == 0) {
            --(*hashTable)->numberOfElements;
            if (element->next == NULL) {
                --(*hashTable)->numberOfSegments;
            }
            delete(word, &((*hashTable)->values[hash]));
            break;
        }
        element = element->next;
    }
    return;
}

void put(char *word, HashTable *hashTable) {
    int hash = getHash(word);
    if(isEmpty(hashTable->values[hash])) {
        push(&(hashTable->values[hash]), 1, word);
        ++hashTable->numberOfElements;
        ++hashTable->numberOfSegments;
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
    int module = 2;
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

int occupancyRate(HashTable *hashTable) {
    return (hashTable->numberOfSegments == 0) ? 1 : (int)(hashTable->numberOfElements/hashTable->numberOfSegments);
}

int maxSegmentSize(HashTable *hashTable) {
    int max = hashTable->values[0]->size;
    for (int i = 1; i < 997; ++i) {
        if (hashTable->values[i]->size > max) {
            max = hashTable->values[i]->size;
        }
    }
    return max;
}

//int averageSegmentSize(HashTable *hashTable) {
//    int *sizes = (int*) calloc(hashTable->numberOfSegments, sizeof(int));
//    int index = 0;
//    for (int i = 0; i < 997; ++i) {
//        if (hashTable->values[i]->size != 0) {
//            sizes[index] = hashTable->values[i]->size;
//            ++index;
//        }
//    }
//    for (int i = 1; i < index; ++i) {
//        if (sizes[i - 1] > si)
//    }
//}