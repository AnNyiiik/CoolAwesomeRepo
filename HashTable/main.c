#include <stdio.h>
#include "hashTable.h"
#include "../List/list.h"

int main() {
    HashTable *hashTable = createHashTable();
    put("fox", hashTable);
    put("apple", hashTable);
    put("snake", hashTable);
    deleteWord("apple", &hashTable);
    deleteHashTable(&hashTable);
    return 0;
}
