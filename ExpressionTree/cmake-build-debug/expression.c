#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
    char character = source[3];
    int index = 0;
    if (character != '(') {
        character = source[3];
        while (character != ' ') {
            operandFirst[index] = character;
            ++index;
            character = source[3 + index];
        }
    } else {
        int countBrackets = 1;
        index = 0;
        char character = ' ';
        while (countBrackets != 0) {
            character = *(source + index + 3);
            if (character == ')') {
                --countBrackets;
            } else if (character == '(' && index != 0) {
                ++countBrackets;
            }
            operandFirst[index] = character;
            ++index;
        }
    }
    character = *(source + index + 4);
    if (character == '(') {
        int countBrackets = 1;
        int number = index + 4;
        int index = 0;
        while (countBrackets != 0) {
            character = *(source + index + number);
            if (character == ')') {
                --countBrackets;
            } else if (character == '(' && index != 0) {
                ++countBrackets;
            }
            operandSecond[index] = character;
            ++index;
        }
    } else {
        int number = index + 4;
        int index = 0;
        character = *(source + index + number);
        while (character != ')') {
            operandSecond[index] = character;
            ++index;
            character = *(source + index + number);
        }
    }
    return;
}

BinaryTree *makeTree(char *expression) {
    if (expression[0] != '(') {
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

void printTree(BinaryTree *tree) {
    printExpression(tree->root, true);
}

int count(BinaryTree *tree) {
    return countExpression(tree->root);
}

int countExpression(Node *root) {
    if (root->left == NULL) {
        return atoi(root->value);
    }
    int operandFirst = countExpression(root->left);
    int operandSecond = countExpression(root->right);
    return implementOperation(root->value, operandFirst, operandSecond);
}

int implementOperation(char *operation, int operandFirst, int operandSecond) {
    if (operation[0] == '+') {
        return operandFirst + operandSecond;
    } else if (operation[0] == '-') {
        return operandFirst - operandSecond;
    } else if (operation[0] == '*') {
        return operandFirst * operandSecond;
    } else {
        return operandFirst / operandSecond;
    }
}
void printExpression(Node *root, bool isFirst) {
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL && root->right != NULL) {
        printf("%s%s%s", "(", root->value, " ");
        printExpression(root->left, true);
        printExpression(root->right, false);
        if (isFirst) {
            printf("%s", ") ");
        } else {
            printf("%s", ")");
        }
    } else {
        if (isFirst) {
            printf("%s%s", root->value, " ");
        } else {
            printf("%s", root->value);
        }
    }
    return;
}

