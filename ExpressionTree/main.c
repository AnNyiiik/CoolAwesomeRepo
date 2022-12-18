#include <stdio.h>
#include "test.h"
#include "expression.h"

int main() {
    if (!testCreateTree() || !testClear()) {
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
    char treeRepresentation[STR_SIZE] = {0};
    int error = 0;
    fgets(treeRepresentation, STR_SIZE, file);
    fclose(file);
    BinaryTree *tree = makeTree(treeRepresentation, &error);
    if (error == 1) {
        return 1;
    }
    printf("To print prefix tree representation enter 1\nto count expression enter 2\nto exit enter 0\n");
    int option = 1;
    while (option != 0) {
        scanf("%d", &option);
        if (option == 0) {
            error = clear(&tree);
            break;
        } else if (option == 1) {
            printTree(tree);
            printf("\n");
        } else {
            int answer = count(tree);
            printf("%d\n", answer);
        }
    }
    error = clear(&tree);
    return error;
}
