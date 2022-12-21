#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "expression.h"

typedef struct Node {
    char value[STR_SIZE];
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BinaryTree {
    Node *root;
} BinaryTree;

Node *createNode(int *error, char *value) {
    Node *root = (Node *)calloc(1, sizeof(Node));
    *error = 0;
    if (root == NULL) {
        *error = 1;
    }
    strcpy(root->value, value);
    return root;
}

BinaryTree *createTree(int *error) {
    BinaryTree *tree = (BinaryTree *)calloc(1, sizeof(BinaryTree));
    *error = 0;
    if (tree == NULL) {
        *error = 1;
    }
    return tree;
}

void parseOperand(char const *source, char *operand, int *index) {
    char character = source[*index];
    int start = *index;
    if (character != '(') {
        while (character != ' ' && character != ')') {
            operand[*index - start] = character;
            ++(*index);
            character = source[*index];
        }
    } else {
        int countBrackets = 1;
        while (countBrackets != 0) {
            character = source[*index];
            if (character == ')') {
                --countBrackets;
            } else if (character == '(' && *index != start) {
                ++countBrackets;
            }
            operand[*index - start] = character;
            ++(*index);
        }
    }
}

void parseOperands(char const *source, char *operation, char *operandFirst, char *operandSecond) {
    operation[0] = source[1];
    int index = 3;
    parseOperand(source, operandFirst, &index);
    ++index;
    parseOperand(source, operandSecond, &index);
}

BinaryTree *makeTree(char *expression, int *error) {
    *error = 0;
    if (expression[0] != '(') {
        BinaryTree *tree = createTree(error);
        if (*error == 1) {
            return NULL;
        }
        Node *root = createNode(error, expression);
        if (*error == 1) {
            return NULL;
        }
        tree->root = root;
        return tree;
    }
    BinaryTree *tree = createTree(error);
    if (*error == 1) {
        return NULL;
    }
    char operation[1] = {0};
    char operandFirst[STR_SIZE] = {0};
    char operandSecond[STR_SIZE] = {0};
    parseOperands(expression, operation, operandFirst, operandSecond);
    BinaryTree *underTreeLeft = makeTree(operandFirst, error);
    if (*error == 1) {
        clear(&tree);
        return NULL;
    }
    BinaryTree *underTreeRight = makeTree(operandSecond, error);
    if (*error == 1) {
        clear(&tree);
        clear(&underTreeLeft);
        return NULL;
    }
    Node *root = createNode(error, operation);
    if (*error == 1) {
        clear(&tree);
        clear(&underTreeRight);
        clear(&underTreeLeft);
        return NULL;
    }
    root->left = underTreeLeft->root;
    root->right = underTreeRight->root;
    tree->root = root;
    return tree;
}

int clearTree(Node **root) {
    if ((*root) == NULL) {
        return 1;
    }
    clearTree(&((*root)->right));
    clearTree(&((*root)->left));
    free(*root);
    *root = NULL;
    return 0;
}

int clear(BinaryTree **tree) {
    if (*tree == NULL) {
        return 1;
    }
    clearTree(&((*tree)->root));
    *tree = NULL;
    return 0;
}

void printExpression(Node *root, bool isFirst) {
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL && root->right != NULL) {
        printf("(%s ", root->value);
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
}

void printTree(BinaryTree *tree) {
    printExpression(tree->root, true);
}

int implementOperation(char const *operation, int operandFirst, int operandSecond) {
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

int countExpression(Node *root) {
    if (root->left == NULL) {
        return atoi(root->value);
    }
    int operandFirst = countExpression(root->left);
    int operandSecond = countExpression(root->right);
    return implementOperation(root->value, operandFirst, operandSecond);
}

int count(BinaryTree *tree) {
    return countExpression(tree->root);
}
