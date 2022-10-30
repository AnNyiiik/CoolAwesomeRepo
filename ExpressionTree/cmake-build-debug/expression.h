#ifndef EXPRESSIONTREE_EXPRESSION_H
#define EXPRESSIONTREE_EXPRESSION_H
typedef struct BinaryTree BinaryTree;

BinaryTree *createTree(void);

void parseOperands(char *source, char *operation, char *operandFirst, char *operandSecond);

BinaryTree *makeTree(char *expression);

void printExpression(BinaryTree *tree, char *expression);
#endif //EXPRESSIONTREE_EXPRESSION_H
