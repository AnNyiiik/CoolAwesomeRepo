#include "test.h"
#include "tree.h"
#include "stdlib.h"
#include <string.h>
typedef struct Node {
    int key;
    int balance;
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
    addElement(3, "aboba", &tree);
    addElement(2, "jojo", &tree);
    addElement(4, "biba", &tree);
    addElement(5, "boba", &tree);
    addElement(6, "abobal", &tree);
    if (tree->root == NULL) {
        return false;
    }
    if (tree->root->key != 3) {
        return false;
    }
    if (tree->root->left == NULL) {
        return false;
    }
    if (tree->root->left->key != 2) {
        return false;
    }
    if (tree->root->right == NULL) {
        return false;
    }
    if (tree->root->right->key != 5) {
        return false;
    }
    if (tree->root->right->right == NULL) {
        return false;
    }
    if (tree->root->right->right->key != 6) {
        return false;
    }
    if (tree->root->right->left == NULL) {
        return false;
    }
    if (tree->root->right->left->key != 4) {
        return false;
    }
    clearTree(&(tree->root));
    addElement(5, "aboba", &tree);
    addElement(4, "jojo", &tree);
    addElement(6, "biba", &tree);
    addElement(3, "boba", &tree);
    addElement(2, "abobal", &tree);
    if (tree->root == NULL) {
        return false;
    }
    if (tree->root->key != 5) {
        return false;
    }
    if (tree->root->left == NULL) {
        return false;
    }
    if (tree->root->left->key != 3) {
        return false;
    }
    if (tree->root->left->left == NULL) {
        return false;
    }
    if (tree->root->left->left->key != 2) {
        return false;
    }
    if (tree->root->left->right == NULL) {
        return false;
    }
    if (tree->root->left->right->key != 4) {
        return false;
    }
    if (tree->root->right == NULL) {
        return false;
    }
    if (tree->root->right->key != 6) {
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
    addElement(5, "jojo", &tree);
    addElement(2, "amogus", &tree);
    addElement(6, "abobal", &tree);
    addElement(1, "abobus", &tree);
    addElement(4, "lupa", &tree);
    addElement(7, "boba", &tree);
    addElement(3, "aiwot", &tree);
    deleteElement(7, &tree);
    if (tree->root == NULL) {
        return false;
    }
    if (tree->root->key != 4) {
        return false;
    }
    if (tree->root->left == NULL) {
        return false;
    }
    if (tree->root->left->key != 2) {
        return false;
    }
    if (tree->root->right == NULL) {
        return false;
    }
    if (tree->root->right->key != 5) {
        return false;
    }
    if (tree->root->left->left == NULL) {
        return false;
    }
    if (tree->root->left->left->key != 1) {
        return false;
    }
    if (tree->root->left->right == NULL) {
        return false;
    }
    if (tree->root->left->right->key != 3) {
        return false;
    }
    if (tree->root->right->right == NULL) {
        return false;
    }
    if (tree->root->right->right->key != 6) {
        return false;
    }
    clearTree(&(tree->root));
    addElement(3, "jojo", &tree);
    addElement(2, "amogus", &tree);
    addElement(6, "abobal", &tree);
    addElement(1, "abobus", &tree);
    addElement(4, "lupa", &tree);
    addElement(7, "boba", &tree);
    addElement(5, "aiwot", &tree);
    deleteElement(1, &tree);
    if (tree->root == NULL) {
        return false;
    }
    if (tree->root->key != 4) {
        return false;
    }
    if (tree->root->left == NULL) {
        return false;
    }
    if (tree->root->left->key != 3) {
        return false;
    }
    if (tree->root->right == NULL) {
        return false;
    }
    if (tree->root->right->key != 6) {
        return false;
    }
    if (tree->root->left->left == NULL) {
        return false;
    }
    if (tree->root->left->left->key != 2) {
        return false;
    }
    if (tree->root->right->right == NULL) {
        return false;
    }
    if (tree->root->right->right->key != 7) {
        return false;
    }
    if (tree->root->right->left == NULL) {
        return false;
    }
    if (tree->root->right->left->key != 5) {
        return false;
    }
    clear(&tree);
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