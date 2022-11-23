#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
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

int sortTree(BinaryTree *tree, int *data, int size) {
    List *list = createList();
    inorder(tree->root, list);
    for (int i = size - 1; i >= 0; --i) {
        int errorCode = pop(&list, &data[i]);
        if (errorCode == 1) {
            deleteList(&list);
            return 1;
        }
    }
    int errorCode = deleteList(&list);
    if (errorCode == 1) {
        return 1;
    }
    return 0;
}

void inorder(Node *root, List *list) {
    if (root == NULL) {
        return;
    }
    inorder(root->left, list);
    pushFront(&list, root->key);
    inorder(root->right, list);
}

int addElement(int key, char *value, BinaryTree **tree) {
    if (*tree == NULL) {
        return 1;
    }
    if ((*tree)->root == NULL) {
        Node *newElement = (Node *) malloc(sizeof(Node));
        newElement->value = (char *) malloc(sizeof(char) * 30);
        strcpy(newElement->value, value);
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
                newElement->value = (char *) malloc(sizeof(char) * 30);
                strcpy(newElement->value, value);
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
                newElement->value = (char *) malloc(sizeof(char) * 30);
                strcpy(newElement->value, value);
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
}

int findValue(int key, BinaryTree *tree, bool *isExits, char *value) {
    if (tree == NULL) {
        return 1;
    }
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
    return 0;
}
int clear(BinaryTree **tree) {
    if (*tree == NULL) {
        return 1;
    }
    clearTree(&((*tree)->root));
    (*tree) = NULL;
}

int clearTree(Node **root) {
    if ((*root) == NULL) {
        return 0;
    }
    clearTree(&((*root)->right));
    clearTree(&((*root)->left));
    free((*root)->value);
    free(*root);
    *root = NULL;
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
        free(element->value);
        free(element);
        return 0;
    }
    if (element->left == NULL) {
        if (previous->right == element) {
            previous->right = element->right;
            free(element->value);
            free(element);
            return 0;
        } else {
            previous->left = element->right;
            free(element->value);
            free(element);
            return 0;
        }
    } else if (element->right == NULL) {
        if (previous->right == element) {
            previous->right = element->left;
            free(element->value);
            free(element);
            return 0;
        } else {
            previous->left = element->left;
            free(element->value);
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
        free(element->value);
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
    free(element->value);
    element->value = elementCopy->value;
    free(elementCopy);
    return 0;
}



