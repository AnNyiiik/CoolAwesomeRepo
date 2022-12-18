#ifndef BINARYTREE_TREE_H
#define BINARYTREE_TREE_H

#include <stdbool.h>

typedef struct BinaryTree BinaryTree;

//Create tree.
BinaryTree *createTree(void);

//Add a new element to a tree.
int addElement(char *key, char *value, BinaryTree **tree);

//Find element by key in the tree.
int findValue(char *key, BinaryTree *tree, bool *isExits, char *value);

//Delete element by key.
int deleteElement(char const *key, BinaryTree **tree);

//Clear tree.
int clear(BinaryTree **tree);

#endif //BINARYTREE_TREE_H
