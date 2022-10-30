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
    BinaryTree *tree = createTree();
    addElement(2, "amogus", &tree);
    addElement(4, "aboba", &tree);
    addElement(3, "jojo", &tree);
    addElement(5, "biba", &tree);
    addElement(1, "boba", &tree);
    clear(&tree);
    return 0;
}
