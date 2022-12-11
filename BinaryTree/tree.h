#ifndef BINARYTREE_TREE_H
#define BINARYTREE_TREE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct BinaryTree BinaryTree;

//Create tree.
BinaryTree *createTree(void);

//Check if a given tree is empty.
bool isEmpty(BinaryTree *tree);

//Add element to a given tree by key.
int addElement(int key, char *value, BinaryTree **tree);

//Find a value in a tree by key.
int findValue(int key, BinaryTree *tree, bool *isExits, char *value, size_t bufferSize);

//Delete an element in a given tree by key.
int deleteElement(int key, BinaryTree **tree);

//Clear a given tree.
int clear(BinaryTree **tree);

#endif //BINARYTREE_TREE_H
