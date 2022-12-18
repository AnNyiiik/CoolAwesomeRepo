#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "expression.h"

#define STR_SIZE 100

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
    char *treeRepresentation = (char *)malloc(sizeof(char) * STR_SIZE);
    int error = 0;
    while (fgets(treeRepresentation, STR_SIZE, file) != NULL) {
        fgets(treeRepresentation, STR_SIZE, file);
        BinaryTree *tree = makeTree(treeRepresentation, &error);
        if (error == 1) {
            break;
        }
        printf("To print prefix tree representation enter 1\nto count expression enter 2\nto exit enter 0\n");
        int option = 0;
        scanf("%d", &option);
        if (option == 0) {
            error = clear(&tree);
            break;
        } else if (option == 1){
            printTree(tree);
            printf("\n");
        } else {
            int answer = count(tree);
            printf("%d\n", answer);
        }
        error = clear(&tree);
    }

    free(treeRepresentation);
    fclose(file);
    return error;
}
