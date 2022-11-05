#include "tree.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct Node {
    int key;
    int height;
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

void fixHeight(Node **node) {
    if ((*node)->left == NULL && (*node)->right == NULL) {
        (*node)->height = 0;
    } else if ((*node)->left == NULL) {
        (*node)->height = (*node)->right->height + 1;
    } else if ((*node)->right == NULL) {
        (*node)->height = (*node)->left->height + 1;
    } else {
        (*node)->height = ((*node)->right->height >= (*node)->left->height) ? ((*node)->right->height + 1) : ((*node)->left->height + 1);
    }
    return;
}

int countBalance(Node *node) {
    if (node == NULL) {
        return 0;
    }
    if (node->right == NULL && node->left == NULL) {
        return 0;
    } else if (node->right == NULL) {
        return -(node->height);
    } else if (node->left == NULL) {
        return (node->height);
    } else {
        return (node->right->height - node->left->height);
    }
}

int add(int key, char *value, Node **node) {
    if ((*node)->key == key) {
        strcpy((*node)->value, value);
    }else if ((*node)->key > key && (*node)->left == NULL) {
        Node *newElement = (Node *) malloc(sizeof(Node));
        newElement->value = (char *) malloc(sizeof(char) * 30);
        strcpy(newElement->value, value);
        newElement->key = key;
        newElement->height = 0;
        newElement->right = NULL;
        newElement->left = NULL;
        (*node)->left = newElement;
        fixHeight(&(*node));
        return 0;
    } else if ((*node)->key < key && (*node)->right == NULL) {
        Node *newElement = (Node *) malloc(sizeof(Node));
        newElement->value = (char *) malloc(sizeof(char) * 30);
        strcpy(newElement->value, value);
        newElement->key = key;
        newElement->height = 0;
        newElement->right = NULL;
        newElement->left = NULL;
        (*node)->right = newElement;
        fixHeight(&(*node));
        return 0;
    } else if ((*node)->key > key) {
        add(key, value, &((*node)->left));
        fixHeight(&(*node));
        *node = balance(&(*node));
    } else {
        add(key, value, &((*node)->right));
        fixHeight(&(*node));
        *node = balance(&(*node));
    }
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
        newElement->height = 0;
        newElement->right = NULL;
        newElement->left = NULL;
        (*tree)->root = newElement;
        return 0;
    } else {
        add(key, value, &((*tree)->root));
        (*tree)->root = balance(&((*tree)->root));
    }
}

Node *rotateRight(Node **node) {
    Node *q = (*node)->left;
    (*node)->left = q->right;
    q->right = (*node);
    fixHeight(&(*node));
    fixHeight(&q);
    return q;
}

Node *rotateLeft(Node **node) {
    Node *q = (*node)->right;
    (*node)->right = q->left;
    q->left = (*node);
    fixHeight(&(*node));
    fixHeight(&q);
    return q;
}

Node *balance(Node **node) {
    fixHeight(&(*node));
    int balance = countBalance((*node));
    if (balance == 2) {
        if (countBalance((*node)->right) < 0) {
            (*node)->right = rotateRight(&((*node)->right));
            fixHeight(&((*node)->right));
        }
        fixHeight(&(*node));
        return rotateLeft(&(*node));
    }
    if(balance == -2) {
        if (countBalance((*node)->left) > 0) {
            (*node)->left = rotateLeft(&((*node)->left));
            fixHeight(&((*node)->left));
        }
        fixHeight(&(*node));
        return rotateRight(&(*node));
    }
    return (*node);
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
        }else {
            previous->left = NULL;
        }
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



