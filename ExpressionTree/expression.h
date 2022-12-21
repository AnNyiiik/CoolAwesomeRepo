#ifndef EXPRESSIONTREE_EXPRESSION_H
#define EXPRESSIONTREE_EXPRESSION_H

#include "stdbool.h"

#define STR_SIZE 100

typedef struct BinaryTree BinaryTree;

// Create tree.
BinaryTree *createTree(int *error);

// Create expression tree according to given expression.
BinaryTree *makeTree(char *expression, int *error);

// Print tree's expression.
void printTree(BinaryTree *tree);

// Count tree's expression.
int count(BinaryTree *tree);

// Clear and delete tree.
int clear(BinaryTree **tree);

#endif //EXPRESSIONTREE_EXPRESSION_H
