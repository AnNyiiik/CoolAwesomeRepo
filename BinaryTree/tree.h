#include <stdbool.h>
#ifndef BINARYTREE_TREE_H
#define BINARYTREE_TREE_H
typedef struct Node Node;

typedef struct BinaryTree BinaryTree;

BinaryTree *createTree(void);

int addElement(int key, char *value, BinaryTree **tree);

int findValue(int key, BinaryTree *tree, bool *isExits, char *value);

int deleteElement(int key, BinaryTree **tree);

int clearTree(BinaryTree **tree);
#endif //BINARYTREE_TREE_H
