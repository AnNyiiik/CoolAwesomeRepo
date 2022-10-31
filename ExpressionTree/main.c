#include <stdio.h>
#include <stdlib.h>
#include "cmake-build-debug/expression.h"
int main() {
    char *expression = "(+ (+ 1 1) (* -12 2))";
    BinaryTree *tree = makeTree(expression);
    printTree(tree);
    //int result = count(tree);
    //printf("%d", result);
    return 0;
}
