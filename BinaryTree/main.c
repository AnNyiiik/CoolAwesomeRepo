#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"
#include "test.h"

int main() {
    if (!testCreateTree()) {
        return 1;
    }
    if (!testAddElement()) {
        return 1;
    }
    if (!testFind()) {
        return 1;
    }
    if (!testClear()) {
        return 1;
    }
    if (!testDeleteElement()) {
        return 1;
    }
    BinaryTree *tree = createTree();
    addElement(4, "jojo", &tree);
    addElement(3, "amogus", &tree);
    addElement(1, "aboba", &tree);
    addElement(2, "abobus", &tree);
    addElement(0, "pupa", &tree);
    addElement(5, "lupa", &tree);
    addElement(6, "boba", &tree);
    deleteElement(0, &tree);
    bool isExists = false;
    char * value = (char *) malloc(sizeof(char) * 30);
    findValue(0, tree, &isExists, value);
    clear(&tree);
    return 0;
}
