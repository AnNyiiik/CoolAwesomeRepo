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

void delete(int key, Node **node, Node **previous) {
    if ((*node) != NULL && (*node)->key != key) {
        if (key > (*node)->key) {
            delete(key, &((*node)->right), &(*node));
            fixHeight(&(*node));
            (*node) = balance(&(*node));
        } else {
            delete(key, &((*node)->left), &(*node));
            fixHeight(&(*node));
            (*node) = balance(&(*node));
        }
    } else {
        if ((*node) == NULL) {
            return;
        }
        if ((*node)->left == NULL && (*node)->right == NULL) {
            if ((*previous)->right == (*node)) {
                free((*node)->value);
                free(*node);
                (*previous)->right = NULL;
            }else {
                free((*node)->value);
                free(*node);
                (*previous)->left = NULL;
            }
            return;
        }
        if ((*node)->left == NULL) {
            if ((*previous)->right == (*node)) {
                (*previous)->right = (*node)->right;
                free((*node)->value);
                free(*node);
                return;
            } else {
                (*previous)->left = (*node)->right;
                free((*node)->value);
                free(*node);
                return;
            }
        } else if ((*node)->right == NULL) {
            if ((*previous)->right == (*node)) {
                (*previous)->right = (*node)->left;
                free((*node)->value);
                free(*node);
                return;
            } else {
                (*previous)->left = (*node)->left;
                free((*node)->value);
                free(*node);
                return;
            }
        } else {
            Node *deletedNode = deleteMax(key, &((*node)->left), &(*node));
            fixHeight(&(*node));
            (*node)->key = deletedNode->key;
            strcpy((*node)->value, deletedNode->value);
            free(deletedNode->value);
            free(deletedNode);
            (*node) = balance(&node);
            return;
        }

    }
}

Node *deleteMax(int key, Node **node, Node **previous) {
    if ((*node)->right != NULL) {
        deleteMax(key, &((*node)->right), &(*node));
        fixHeight(&(*node));
        (*node) = balance(&(*node));
    }else {
        if ((*node)->left == NULL) {
            (*previous)->right = NULL;
            return (*node);
        } else {
            (*previous)->right = (*node)->left;
            return (*node);
        }
    }
}
int deleteElement(int key, BinaryTree **tree) {
    if (*tree == NULL) {
        return 1;
    }
    if ((*tree)->root == NULL) {
        return 0;
    }
    if ((*tree)->root->key == key) {
        free((*tree)->root->value);
        free((*tree)->root);
        (*tree)->root = NULL;
        return 0;
    }
    delete(key, &((*tree)->root), &((*tree)->root));
    fixHeight(&((*tree)->root));
    (*tree)->root = balance(&((*tree)->root));
    return 0;
}



