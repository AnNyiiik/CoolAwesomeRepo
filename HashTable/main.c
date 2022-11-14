#include <stdio.h>
#include "hashTable.h"
#include "../List/list.h"

int main() {
    HashTable *hashTable = createHashTable();
    put("fox", hashTable);
    put("fox", hashTable);
    deleteHashTable(&hashTable);
    return 0;
}
