#include <stdio.h>
#include <stdlib.h>
#include "cmake-build-debug/expression.h"
int main() {
    char *expression = "(+(*(+12)3)(-2(*24)))";
    BinaryTree *tree = makeTree(expression);
    int result = count(tree);
    printf("%d", result);
    return 0;
}
