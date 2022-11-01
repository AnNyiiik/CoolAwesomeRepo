#include "test.h"
#include <string.h>
#include "cmake-build-debug/expression.h"
typedef struct Node {
    char *value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BinaryTree {
    Node *root;
} BinaryTree;

bool testMakeTree(void) {
    char *testData[3] = {"(* (+ 1 1) 2)", "(* (* (+ 1 2) 8) 2)"};
    for (int i = 0; i < 2; ++ i) {
        BinaryTree *tree = makeTree(testData[i]);
        if (i == 0) {
            if (strcmp(tree->root->value, "*") != 0 || strcmp(tree->root->left->value, "+") != 0 || strcmp(tree->root->left->left->value, "1") != 0
            || strcmp(tree->root->left->right->value, "1") != 0 || strcmp(tree->root->right->value, "2") != 0) {
                clear(&tree);
                return false;
            }
        } else if (i == 1) {
            if (strcmp(tree->root->value, "*") != 0 || strcmp(tree->root->left->value, "*") != 0 || strcmp(tree->root->left->left->value, "+") != 0
                || strcmp(tree->root->left->right->value, "8") != 0 || strcmp(tree->root->left->left->left->value, "1") != 0
                || strcmp(tree->root->left->left->right->value, "2") != 0 || strcmp(tree->root->right->value, "2") != 0) {
                clear(&tree);
                return false;
            }
        }
        clear(&tree);
    }
    return true;
}

bool testCalculate(void) {
    char *testData[5] = {"(* (+ 1 1) 2)", "(* (* (+ 1 2) 8) 2)", "(- (- -12 13) (* 5 12))",
                         "(/ 15 (* 5 3))", "(+ (* -4 7) (- 15 (/ -12 (+ 2 4))))"};
    int correctAnswers[5] = {4, 48, -85, 1, -11};
    for (int i = 0; i < 5; ++i) {
        BinaryTree *tree = makeTree(testData[i]);
        int answer = count(tree);
        if (answer != correctAnswers[i]) {
            clear(&tree);
            return false;
        }
        clear(&tree);
    }
    return true;
}