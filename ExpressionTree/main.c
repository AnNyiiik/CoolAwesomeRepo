#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "cmake-build-debug/expression.h"
int main() {
    if (!testMakeTree()) {
        printf("Test make tree has been failed");
        return 1;
    }
    if (!testCalculate()) {
        printf("Test calculate has been failed");
        return 1;
    }
    FILE *file = fopen("../tree", "r");
    if (file == NULL) {
        printf("file not found");
    }
    char *treeRepresentation = (char *) malloc(sizeof(char) * 100);
    while (fgets(treeRepresentation, 100, file) != NULL) {
        fgets(treeRepresentation, 100, file);
        BinaryTree *tree = makeTree(treeRepresentation);
        printf("To print prefix tree representation enter 1\nto count expression enter 2\nto exit enter 0\n");
        int option = 0;
        scanf("%d", &option);
        if (option == 0) {
            clear(tree);
            break;
        } else if (option == 1){
            printTree(tree);
            printf("\n");
        } else {
            count(tree);
            printf("\n");
        }
        clear(tree);
    }
    free(treeRepresentation);
    fclose("../tree");
    return 0;
}
