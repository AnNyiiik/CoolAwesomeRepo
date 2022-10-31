#ifndef EXPRESSIONTREE_EXPRESSION_H
#define EXPRESSIONTREE_EXPRESSION_H
typedef struct BinaryTree BinaryTree;

typedef struct Node Node;

BinaryTree *createTree(void);

void parseOperands(char *source, char *operation, char *operandFirst, char *operandSecond);

BinaryTree *makeTree(char *expression);

void printExpression(Node *root);

void printTree(BinaryTree *tree);

int implementOperation(char *operation, int operandFirst, int operandSecond);

int countExpression(Node *root);

int count(BinaryTree *tree);

int clear(BinaryTree **tree);

int clearTree(Node **root);
#endif //EXPRESSIONTREE_EXPRESSION_H
