#include "tree.h"
#include <stdlib.h>
#include <stdbool.h>
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

BinaryTree *createTree(void) {
    BinaryTree *tree = (BinaryTree *) malloc(sizeof(BinaryTree *));
    tree->root = NULL;
    return tree;
}

int addElement(int key, char *value, BinaryTree **tree) {
    if ((*tree)->root == NULL) {
        Node *newElement = (Node *) malloc(sizeof(Node));
        newElement->value = value;
        newElement->key = key;
        newElement->right = NULL;
        newElement->left = NULL;
        (*tree)->root = newElement;
        return 0;
    }
    Node *element = (*tree)->root;
    while(element != NULL) {
        if (key == element->key) {
            element->value = value;
            return 0;
        } else if (key > element->key) {
            if (element->right == NULL) {
                Node *newElement = (Node *) malloc(sizeof(Node));
                newElement->value = value;
                newElement->key = key;
                newElement->right = NULL;
                newElement->left = NULL;
                element->right = newElement;
                return 0;
            }
            element = element->right;
        } else {
            if (element->left == NULL) {
                Node *newElement = (Node *) malloc(sizeof(Node));
                newElement->value = value;
                newElement->key = key;
                newElement->right = NULL;
                newElement->left = NULL;
                element->left = newElement;
                return 0;
            }
            element = element->left;
        }
    }
    return 1;
};

int findValue(int key, BinaryTree *tree, bool *isExits, char *value) {
    {
        if (tree->root == NULL) {
            *isExits = false;
            return 0;
        }
        Node *element = tree->root;
        while(element != NULL && element->key != key) {
            if (key > element->key) {
                element = element->right;
            } else {
                element = element->left;
            }
        }
        if (element != NULL) {
            strcpy(value, element->value);
            *isExits = true;
            return 0;
        }
        *isExits = false;
        return 1;
    }
}

int clearTree(BinaryTree **tree) {
    if ((*tree)->root == NULL) {
        return 0;
    }
}

int deleteElement(int key, BinaryTree **tree) {
    if ((*tree)->root == NULL) {
        return 0;
    }
    Node *element = (*tree)->root;
    Node *previous = (*tree)->root;
    while(element != NULL && element->key != key) {
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
        element->value = elementCopy->value;
        if (previous == element) {
            element->left = NULL;
        } else {
            previous->right = NULL;
        }
        free(elementCopy);
        return 0;
    }
    previous->right = elementCopy->left;
    element->key = elementCopy->key;
    element->value = elementCopy->value;
    free(elementCopy);
    return 0;
}



