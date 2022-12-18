#include "tree.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    char key[30];
    int height;
    char value[100];
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BinaryTree {
    Node *root;
} BinaryTree;

BinaryTree *createTree(void) {
    BinaryTree *tree = (BinaryTree *)calloc(1, sizeof(BinaryTree));
    return tree;
}

Node *createNode(char *key, char *value) {
    Node *node = (Node *)calloc(1, sizeof(Node));
    strcpy(node->value, value);
    strcpy(node->key, key);
    return node;
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

void add(char *key, char *value, Node **node) {
    if ((*node)->key == key) {
        strcpy((*node)->value, value);
    }else if (strcmp((*node)->key, key) > 0 && (*node)->left == NULL) {
        (*node)->left = createNode(key, value);
        fixHeight(&(*node));
        return;
    } else if (strcmp((*node)->key, key) < 0 && (*node)->right == NULL) {
        (*node)->right = createNode(key, value);
        fixHeight(&(*node));
        return;
    } else if (strcmp((*node)->key, key) > 0) {
        add(key, value, &((*node)->left));
        fixHeight(&(*node));
        *node = balance(&(*node));
        return;
    } else {
        add(key, value, &((*node)->right));
        fixHeight(&(*node));
        *node = balance(&(*node));
        return;
    }
}

int addElement(char *key, char *value, BinaryTree **tree) {
    if (*tree == NULL) {
        return 1;
    }
    if ((*tree)->root == NULL) {
        (*tree)->root = createNode(key, value);
        return 0;
    } else {
        add(key, value, &((*tree)->root));
        (*tree)->root = balance(&((*tree)->root));
    }
}

int findValue(char *key, BinaryTree *tree, bool *isExits, char *value) {
    if (tree == NULL) {
        return 1;
    }
    if (tree->root == NULL) {
        *isExits = false;
        return 0;
    }
    Node *element = tree->root;
    while(element != NULL && strcmp(element->key, key) != 0) {
        if (strcmp(key, element->key) > 0) {
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

int clearTree(Node **root) {
    if ((*root) == NULL) {
        return 0;
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
    (*tree) = NULL;
}

void deleteMax(const char *key, Node **node, Node **previous, Node **maxNode) {
    if ((*node)->right != NULL) {
        deleteMax(key, &((*node)->right), &(*node), &(*maxNode));
        fixHeight(&(*node));
        *node = balance(&(*node));
    } else {
        if ((*node)->left == NULL) {
            *maxNode = *node;
            if ((*previous)->left != (*node)) {
                (*previous)->right = NULL;
            } else {
                (*previous)->left = NULL;
            }
            return;
        } else {
            *maxNode = *node;
            if ((*previous)->left != (*node)) {
                (*previous)->right = (*node)->left;
            } else {
                (*previous)->left = (*node)->left;
            }
            return;
        }
    }
}

void delete(char const *key, Node **node, Node **previous) {
    if ((*node) != NULL && strcmp((*node)->key, key) != 0) {
        if (strcmp(key, (*node)->key) > 0) {
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
                free(*node);
                (*previous)->right = NULL;
            }else {
                free(*node);
                (*previous)->left = NULL;
            }
            return;
        }
        if ((*node)->left == NULL) {
            if ((*previous) == (*node)) {
                strcpy((*node)->value, (*node)->right->value);
                strcpy((*node)->key, (*node)->right->key);
                free((*node)->right);
                (*node)->right = NULL;
                fixHeight(&(*node));
                return;
            }
            if ((*previous)->right == (*node)) {
                strcpy((*node)->value, (*node)->right->value);
                strcpy((*node)->key, (*node)->right->key);
                free((*node)->right);
                (*previous)->right->right = NULL;
                fixHeight(&((*previous)->right));
                return;
            } else {
                strcpy((*node)->value, (*node)->right->value);
                strcpy((*node)->key, (*node)->right->key);
                free((*node)->right);
                (*previous)->left->right = NULL;
                fixHeight(&((*previous)->left));
                return;
            }
        } else if ((*node)->right == NULL) {
            if ((*previous) == (*node)) {
                strcpy((*node)->value, (*node)->left->value);
                strcpy((*node)->key, (*node)->left->key);
                free((*node)->left);
                (*node)->left = NULL;
                fixHeight(&(*node));
                return;
            }
            if ((*previous)->right == (*node)) {
                strcpy((*previous)->right->value, (*node)->left->value);
                strcpy((*previous)->right->key, (*node)->left->key);
                free((*node)->left);
                (*previous)->right->left = NULL;
                fixHeight(&((*previous)->right));
                return;
            } else {
                strcpy((*previous)->left->value, (*node)->left->value);
                strcpy((*previous)->left->key, (*node)->left->key);
                free((*node)->left);
                (*previous)->left->left = NULL;
                fixHeight(&((*previous)->left));
                return;
            }
        } else {
            Node *deletedNode = NULL;
            deleteMax(key, &((*node)->left), &(*node), &(deletedNode));
            fixHeight(&(*node));
            strcpy((*node)->key, deletedNode->key);
            strcpy((*node)->value, deletedNode->value);
            free(deletedNode);
            (*node) = balance(&(*node));
            return;
        }
    }
}

int deleteElement(char const *key, BinaryTree **tree) {
    if (*tree == NULL) {
        return 1;
    }
    if ((*tree)->root == NULL) {
        return 0;
    }
    if (((*tree)->root->height == 0) && (strcmp(key, (*tree)->root->key)) == 0) {
        free((*tree)->root);
        (*tree)->root = NULL;
        return 0;
    }
    delete(key, &((*tree)->root), &((*tree)->root));
    fixHeight(&((*tree)->root));
    (*tree)->root = balance(&((*tree)->root));
    return 0;
}



