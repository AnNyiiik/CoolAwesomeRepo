#include "test.h"
#include "tree.h"
#include "stdlib.h"
#include <string.h>
typedef struct Node {
    int key;
    char *value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BinaryTree {
    Node *root;
} BinaryTree;

bool testCreateTree(void) {
    BinaryTree *tree = createTree();
    if (tree == NULL) {
        return false;
    }
    if (tree->root != NULL) {
        clear(&tree);
        return false;
    }
    clear(&tree);
    return true;
}

bool testAddElement(void) {
    BinaryTree *tree = createTree();
    addElement(4, "aboba", &tree);
    if (tree->root == NULL) {
        clear(&tree);
        return false;
    }
    if (!(tree->root->key == 4) || !(strcmp(tree->root->value, "aboba") == 0)) {
        clear(&tree);
        return false;
    }
    addElement(2, "amogus", &tree);
    if (tree->root->left == NULL) {
        clear(&tree);
        return false;
    }
    addElement(5, "pupa", &tree);
    if (tree->root->right == NULL) {
        clear(&tree);
        return false;
    }
    if (!(tree->root->right->key == 5) || !(strcmp(tree->root->right->value, "pupa") == 0)
    || !(tree->root->right->right == NULL) || !(tree->root->right->left == NULL)) {
        clear(&tree);
        return false;
    }
    if (!(tree->root->left->key == 2) || !(strcmp(tree->root->left->value, "amogus") == 0)
    || !(tree->root->left->right == NULL) || !(tree->root->left->left == NULL)) {
        clear(&tree);
        return false;
    }
    clear(&tree);
    return true;
}

bool testFind(void) {
    BinaryTree *tree = createTree();
    bool isExists = false;
    char *value = (char*) malloc(sizeof(char) * 30);
    findValue(2, tree, &isExists, value);
    if (isExists) {
        free(value);
        return false;
    }
    addElement(2, "amogus", &tree);
    findValue(2, tree, &isExists, value);
    if (!isExists) {
        free(value);
        return false;
    }
    addElement(4, "aboba", &tree);
    addElement(3, "jojo", &tree);
    addElement(5, "biba", &tree);
    addElement(1, "boba", &tree);
    findValue(3, tree, &isExists, value);
    if (!isExists) {
        free(value);
        return false;
    }
    findValue(4, tree, &isExists, value);
    if (!isExists) {
        free(value);
        return false;
    }
    free(value);
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
        if (tree->root == NULL) {
            return false;
        }
        bool isExists = false;
        char * value = (char *) malloc(sizeof(char) * 30);
        findValue(deletedKeys[i], tree, &isExists, value);
        if (isExists) {
            free(value);
            return false;
        }
        if (deletedKeys[i] == 0) {
            if (tree->root->left->left->left != NULL || tree->root->left->left->right == NULL) {
                free(value);
                return false;
            }
        }
        if (deletedKeys[i] == 1) {
            if (tree->root->left->left->right != NULL || tree->root->left->left->key != 2
            || strcmp(tree->root->left->left->value, "abobus") != 0) {
                free(value);
                return false;
            }
        }
        if (deletedKeys[i] == 3) {
            if (tree->root->left->left != NULL || tree->root->left->key != 2
            || strcmp(tree->root->left->value, "abobus") != 0) {
                free(value);
                return false;
            }
        }
        if (deletedKeys[i] == 5) {
            if (tree->root->right->right != NULL || tree->root->right->key != 6
                || strcmp(tree->root->right->value, "boba") != 0) {
                free(value);
                return false;
            }
        }
        if (deletedKeys[i] == 4) {
            if (tree->root->key != 2
                || strcmp(tree->root->value, "abobus") != 0 || tree->root->left != NULL) {
                free(value);
                return false;
            }
        }
        free(value);
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