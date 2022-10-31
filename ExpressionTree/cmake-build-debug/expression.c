#include <stdlib.h>
#include <string.h>
#include "expression.h"
typedef struct Node {
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

void parseOperands(char *source, char *operation, char *operandFirst, char *operandSecond) {
    operation[0] = source[1];
    if (strlen(source) == 5) {
        operandFirst[0] = *(source + 2);
        operandSecond[0] = *(source + 3);
        return;
    }
    int countBrackets = 1;
    int index = 0;
    while (countBrackets != 0) {
        char character = *(source + index + 2);
        if (character == ')') {
            --countBrackets;
        } else if (character == '(' && index != 0) {
            ++countBrackets;
        }
        operandFirst[index] = character;
        ++index;
    }
    if (*(source + index + 2) != '(') {
        operandSecond[0] = *(source + index + 2);
        return;
    }
    countBrackets = 1;
    int number = index + 2;
    index = 0;
    while (countBrackets != 0) {
        char character = *(source + index + number);
        if (character == ')') {
            --countBrackets;
        } else if (character == '(' && index != 0) {
            ++countBrackets;
        }
        operandSecond[index] = character;
        ++index;
    }
    return;
}

BinaryTree *makeTree(char *expression) {
    if (strlen(expression) == 1) {
        BinaryTree *tree = createTree();
        Node *root = (Node *) malloc(sizeof(Node));
        root->value = expression;
        root->left = NULL;
        root->right = NULL;
        tree->root = root;
        return tree;
    }
    BinaryTree *tree = createTree();
    char *operation = (char *) malloc(sizeof(char));
    char *operandFirst = (char *) malloc(sizeof(char) * 100);
    char *operandSecond = (char *) malloc(sizeof(char) * 100);
    parseOperands(expression, operation, operandFirst, operandSecond);
    BinaryTree *underTreeLeft = makeTree(operandFirst);
    BinaryTree *underTreeRight = makeTree(operandSecond);
    Node *root = (Node *) malloc(sizeof(Node));
    root->left = underTreeLeft->root;
    root->right = underTreeRight->root;
    root->value = operation;
    tree->root = root;
    return tree;
}

void printExpression(BinaryTree *tree, char *expression) {
    return;
}