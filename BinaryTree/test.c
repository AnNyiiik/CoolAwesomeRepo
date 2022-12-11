#include "test.h"
#include "tree.h"
#include <string.h>
#define BUFFER_VALUE 30

bool testCreateTree(void) {
    BinaryTree *tree = createTree();
    if (tree == NULL) {
        return false;
    }
    return isEmpty(tree);
}

bool testAddElement(void) {
    BinaryTree *tree = createTree();
    addElement(4, "aboba", &tree);
    if (isEmpty(tree)) {
        clear(&tree);
        return false;
    }
    bool isExists = true;
    char value[30] = {0};
    findValue(4, tree, &isExists, value, BUFFER_VALUE);
    if (!isExists || strcmp(value, "aboba") != 0) {
        clear(&tree);
        return false;
    }
    addElement(2, "amogus", &tree);
    findValue(2, tree, &isExists, value, BUFFER_VALUE);
    if (!isExists || strcmp(value, "amogus") != 0) {
        clear(&tree);
        return false;
    }
    clear(&tree);
    return true;
}

bool testFind(void) {
    BinaryTree *tree = createTree();
    bool isExists = false;
    char value[BUFFER_VALUE] = {0};
    findValue(2, tree, &isExists, value, BUFFER_VALUE);
    if (isExists) {
        clear(&tree);
        return false;
    }
    addElement(2, "amogus", &tree);
    findValue(2, tree, &isExists, value, BUFFER_VALUE);
    if (!isExists) {
        clear(&tree);
        return false;
    }
    addElement(4, "aboba", &tree);
    addElement(3, "jojo", &tree);
    addElement(5, "biba", &tree);
    addElement(1, "boba", &tree);
    findValue(3, tree, &isExists, value, BUFFER_VALUE);
    if (!isExists) {
        clear(&tree);
        return false;
    }
    findValue(4, tree, &isExists, value, BUFFER_VALUE);
    if (!isExists) {
        clear(&tree);
        return false;
    }
    clear(&tree);
    return true;
}

bool testDeleteElement(void) {
    BinaryTree *tree = createTree();
    addElement(4, "jojo", &tree);
    addElement(3, "amogus", &tree);
    addElement(1, "aboba", &tree);
    addElement(2, "abobus", &tree);
    addElement(0, "pupa", &tree);
    addElement(5, "lupa", &tree);
    addElement(6, "boba", &tree);
    int deletedKeys[5] = {0, 1, 3, 5, 4};
    for (int i = 0; i < 5; ++i) {
        deleteElement(deletedKeys[i], &tree);
        if (isEmpty(tree)) {
            return false;
        }
        bool isExists = false;
        char value[30] = {0};
        findValue(deletedKeys[i], tree, &isExists, value, BUFFER_VALUE);
        if (isExists) {
            return false;
        }
    }
    return true;
}

bool testClear(void) {
    BinaryTree *tree = createTree();
    clear(&tree);
    if (tree != NULL) {
        return false;
    }
    tree = createTree();
    addElement(3, "jojo", &tree);
    addElement(2, "amogus", &tree);
    addElement(4, "aboba", &tree);
    clear(&tree);
    if (tree != NULL) {
        clear(&tree);
        return false;
    }
    return true;
}