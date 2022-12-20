#include "tree.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int key;
    char value[30];
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BinaryTree {
    Node *root;
} BinaryTree;

bool isEmpty(BinaryTree *tree) {
    if (tree == NULL) {
        return false;
    }
    return tree->root == NULL;
}

BinaryTree *createTree(void) {
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->root = NULL;
    return tree;
}

Node *createNode(int key, char *value, int *errorCode) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        *errorCode = 1;
        return NULL;
    }
    strcpy(node->value, value);
    node->key = key;
    node->right = NULL;
    node->left = NULL;
    *errorCode = 0;
    return node;
}

int addElement(int key, char *value, BinaryTree **tree) {
    if (*tree == NULL) {
        return 1;
    }
    if ((*tree)->root == NULL) {
        int error = 0;
        (*tree)->root = createNode(key, value, &error);
        return error;
    }
    Node *element = (*tree)->root;
    while (element != NULL) {
        if (key == element->key) {
            strcpy(element->value, value);
            return 0;
        } else if (key > element->key) {
            if (element->right == NULL) {
                int error = 0;
                Node *newElement = createNode(key, value, &error);
                if (error == 1) {
                    return 1;
                }
                element->right = newElement;
                return 0;
            }
            element = element->right;
        } else {
            if (element->left == NULL) {
                int error = 0;
                Node *newElement = createNode(key, value, &error);
                if (error == 1) {
                    return 1;
                }
                element->left = newElement;
                return 0;
            }
            element = element->left;
        }
    }
    return 1;
};

int findValue(int key, BinaryTree *tree, bool *isExits, char *value, size_t bufferSize) {
    if (tree == NULL) {
        return 1;
    }
    if (tree->root == NULL) {
        *isExits = false;
        return 0;
    }
    Node *element = tree->root;
    while (element != NULL && element->key != key) {
        if (key > element->key) {
            element = element->right;
        } else {
            element = element->left;
        }
    }
    if (element != NULL) {
        if (strlen(element->value) > bufferSize) {
            strcpy(value, element->value);
            *isExits = true;
            return 1;
        }
        strcpy(value, element->value);
        *isExits = true;
        return 0;
    }
    *isExits = false;
    return 0;
}

void clearTree(Node **root) {
    if (*root == NULL) {
        return;
    }
    clearTree(&((*root)->right));
    clearTree(&((*root)->left));
    free(*root);
    *root = NULL;
}

int clear(BinaryTree **tree) {
    if (*tree == NULL) {
        return 1;
    }
    clearTree(&((*tree)->root));
    *tree = NULL;
    return 0;
}

int deleteElement(int key, BinaryTree **tree) {
    if (*tree == NULL) {
        return 1;
    }
    if ((*tree)->root == NULL) {
        return 0;
    }
    Node *element = (*tree)->root;
    Node *previous = (*tree)->root;
    while (element != NULL && element->key != key) {
        if (key > element->key) {
            previous = element;
            element = element->right;
        } else {
            previous = element;
            element = element->left;
        }
    }
    if (element == NULL) {
        return 0;
    }
    if (element->left == NULL && element->right == NULL) {
        if (element == (*tree)->root) {
            (*tree)->root = NULL;
        }
        if (previous->right == element) {
            previous->right = NULL;
        }
        previous->left = NULL;
        free(element);
        return 0;
    }
    if (element->left == NULL) {
        if (previous->right == element) {
            previous->right = element->right;
            free(element);
            return 0;
        } else {
            previous->left = element->right;
            free(element);
            return 0;
        }
    } else if (element->right == NULL) {
        if (previous->right == element) {
            previous->right = element->left;
            free(element);
            return 0;
        } else {
            previous->left = element->left;
            free(element);
            return 0;
        }
    }
    Node *elementCopy = element->left;
    previous = element;
    while (elementCopy->right != NULL) {
        previous = elementCopy;
        elementCopy = elementCopy->right;
    }
    if (elementCopy->left == NULL) {
        element->key = elementCopy->key;
        strcpy(element->value, elementCopy->value);
        if (previous == element) {
            element->left = NULL;
        } else {
            previous->right = NULL;
        }
        free(elementCopy);
        return 0;
    }
    if (previous == element) {
        element->key = elementCopy->key;
        strcpy(element->value, elementCopy->value);
        element->left = elementCopy->left;
        free(elementCopy);
        return 0;
    }
    previous->right = elementCopy->left;
    element->key = elementCopy->key;
    strcpy(element->value, elementCopy->value);
    free(elementCopy);
    return 0;
}



