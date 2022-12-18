#include "test.h"
#include "string.h"
#include "expression.h"

bool testCreateTree(void) {
    int error = 0;
    BinaryTree *tree = createTree(&error);
    if (error == 1) {
        return false;
    }
    clear(&tree);
    return true;
}

bool testClear(void) {
    int error = 0;
    BinaryTree *tree = makeTree("(* (+ 1 1) 2)", &error);
    error = clear(&tree);
    if (tree != NULL || error != 0) {
        return false;
    }
    return true;
}

bool testCalculate(void) {
    char *testData[5] = {"(* (+ 1 1) 2)", "(* (* (+ 1 2) 8) 2)", "(- (- -12 13) (* 5 12))",
                         "(/ 15 (* 5 3))", "(+ (* -4 7) (- 15 (/ -12 (+ 2 4))))"};
    int correctAnswers[5] = {4, 48, -85, 1, -11};
    int error = 0;
    for (int i = 0; i < 5; ++i) {
        BinaryTree *tree = makeTree(testData[i], &error);
        if (error == 1) {
            return false;
        }
        int answer = count(tree);
        if (answer != correctAnswers[i]) {
            clear(&tree);
            return false;
        }
        clear(&tree);
        if (error == 1) {
            return false;
        }
    }
    return true;
}