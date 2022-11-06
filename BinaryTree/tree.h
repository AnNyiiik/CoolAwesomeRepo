#include <stdbool.h>
#ifndef BINARYTREE_TREE_H
#define BINARYTREE_TREE_H
typedef struct Node Node;

typedef struct BinaryTree BinaryTree;

BinaryTree *createTree(void);

int addElement(int key, char *value, BinaryTree **tree);

int add(int key, char *value, Node **node);

void fixHeight(Node **node);

int countBalance(Node *node);

Node *balance(Node **node);

int findValue(int key, BinaryTree *tree, bool *isExits, char *value);

int deleteElement(int key, BinaryTree **tree);

void delete(int key, Node **node, Node **previous);

Node *deleteMax(int key, Node **node, Node **previous);

int clear(BinaryTree **tree);

int clearTree(Node **root);
#endif //BINARYTREE_TREE_H
