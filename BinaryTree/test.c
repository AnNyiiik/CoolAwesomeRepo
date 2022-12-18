#include "test.h"
#include "tree.h"
#include <string.h>

bool testCreateTree(void) {
    BinaryTree *tree = createTree();
    if (tree == NULL) {
        return false;
    }
    clear(&tree);
    return true;
}

bool testAddElement(void) {
    BinaryTree *tree = createTree();
    addElement("3", "aboba", &tree);
    if (tree == NULL) {
        return false;
    }
    clear(&tree);
    return true;
}

bool testFind(void) {
    BinaryTree *tree = createTree();
    bool isExists = false;
    char value[STR_SIZE] = {0};
    findValue("2", tree, &isExists, value);
    if (isExists) {
        clear(&tree);
        return false;
    }
    addElement("2", "amogus", &tree);
    findValue("2", tree, &isExists, value);
    if (!isExists) {
        clear(&tree);
        return false;
    }
    addElement("4", "aboba", &tree);
    addElement("3", "jojo", &tree);
    addElement("5", "biba", &tree);
    addElement("1", "boba", &tree);
    findValue("3", tree, &isExists, value);
    if (!isExists) {
        clear(&tree);
        return false;
    }
    findValue("4", tree, &isExists, value);
    clear(&tree);
    return isExists;
}

bool testDeleteElement(void) {
    BinaryTree *tree = createTree();
    addElement("5", "jojo", &tree);
    addElement("2", "amogus", &tree);
    addElement("7", "boba", &tree);
    deleteElement("7", &tree);
    char value[STR_SIZE] = {0};
    bool isExists = false;
    findValue("7", tree, &isExists, value);
    clear(&tree);
    return !isExists;
}

bool testClear(void) {
    BinaryTree *tree = createTree();
    clear(&tree);
    if (tree != NULL) {
        return false;
    }
    tree = createTree();
    addElement("3", "jojo", &tree);
    addElement("2", "amogus", &tree);
    addElement("4", "aboba", &tree);
    clear(&tree);
    if (tree != NULL) {
        clear(&tree);
        return false;
    }
    return true;
}