#include <stdio.h>
#include <stdlib.h>
#include "cmake-build-debug/expression.h"
int main() {
    char *expression = "(+(*12)1)";
    BinaryTree *tree = makeTree(expression);
    return 0;
}
