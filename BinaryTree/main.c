#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"

int main() {
    BinaryTree *tree = createTree();
    addElement(2, "amogus", &tree);
    addElement(4, "aboba", &tree);
    addElement(3, "jojo", &tree);
    addElement(5, "biba", &tree);
    addElement(1, "boba", &tree);
    clear(&tree);
}
