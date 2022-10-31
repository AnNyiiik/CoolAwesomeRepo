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
    if (strlen(source) == 5) {
        operandFirst[0] = *(source + 2);
        operandSecond[0] = *(source + 3);
        return;
    }
    if (*(source + 2) == '(' && *(source + 3) != '+' && *(source + 3)
    != '-' && *(source + 3) != '*' && *(source + 3) != '/') {
        int index = 3;
        char character = *(source + 3);
        while (character != ')') {
            operandFirst[index - 3] = character;
            ++index;
            character = *(source + index);
        }
        if (*(source + index + 1) != '(') {
            operandSecond[0] = *(source + index + 1);
        } else {
            index = index + 2;
            int number = index;
            char character = *(source + index);
            while (character != ')') {
                operandSecond[index - number] = character;
                ++index;
                character = *(source + index);
            }
        }
        return;
    }
    if (source[2] != '(') {
        operandFirst[0] = *(source + 2);
        if (*(source + 4) != '+' && *(source + 4) != '-' && *(source + 4) != '*' && *(source + 4) != '/') {
            int index = 4;
            char character = *(source + 4);
            while (character != ')') {
                operandSecond[index - 4] = character;
                ++index;
                character = *(source + index);
            }
            return;
        } else {
            int countBrackets = 1;
            int index = 0;
            while (countBrackets != 0) {
                char character = *(source + index + 3);
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
    if (*(source + index + 3) != '+' && *(source + index + 3) != '-'
    && *(source + index + 3) != '*' && *(source + index + 3) != '/') {
        int number = index + 3;
        int index = 0;
        char character = *(source + number);
        while (character != ')') {
            operandSecond[index] = character;
            ++index;
            character = *(source + number + index);
        }
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
    printExpression(tree->root);
}

int countTree(BinaryTree *tree) {
    return 1;
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
void printExpression(Node *root) {
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL && root->right != NULL) {
        printf("%s%s", "(", root->value);
        printExpression(root->left);
        printExpression(root->right);
        printf("%s", ")");
    } else {
        if (strlen(root->value) > 1) {
            printf("%s%s%s", "(", root->value, ")");
        }else {
            printf("%s", root->value);
        }
    }
    return;
}

