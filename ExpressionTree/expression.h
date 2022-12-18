#ifndef EXPRESSIONTREE_EXPRESSION_H
#define EXPRESSIONTREE_EXPRESSION_H

#include "stdbool.h"

typedef struct BinaryTree BinaryTree;

//Create tree.
BinaryTree *createTree(int *error);

//Split expression string into operation and operands.
void parseOperands(char const *source, char *operation, char *operandFirst, char *operandSecond);

//Create expression tree according to given expression.
BinaryTree *makeTree(char *expression, int *error);

//Print tree's expression.
void printTree(BinaryTree *tree);

//Count tree's expression.
int count(BinaryTree *tree);

//Clear and delete tree.
int clear(BinaryTree **tree);

#endif //EXPRESSIONTREE_EXPRESSION_H
