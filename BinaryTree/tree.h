#include <stdbool.h>
#include "../List/list.h"
#ifndef BINARYTREE_TREE_H
#define BINARYTREE_TREE_H
typedef struct Node Node;

typedef struct BinaryTree BinaryTree;

void inorder(Node *root, List *list);

int sortTree(BinaryTree *tree, int *data, int size);

BinaryTree *createTree(void);

int addElement(int key, char *value, BinaryTree **tree);

int findValue(int key, BinaryTree *tree, bool *isExits, char *value);

int deleteElement(int key, BinaryTree **tree);

int clear(BinaryTree **tree);

int clearTree(Node **root);
#endif //BINARYTREE_TREE_H
