#include <stdio.h>
#include <stdlib.h>
#include "../List/list.h"
#include "../BinaryTree/tree.h"

bool testSymmetric(int *errorCode) {
    FILE *file = fopen("../testFile", "r");
    if (file == NULL) {
        *errorCode = 1;
        return false;
    }
    char *number = (char *)malloc(sizeof(char) * 30);
    if (number == NULL) {
        fclose(file);
        *errorCode = 1;
        return false;
    }
    List *list = createList();
    while ((fscanf(file, "%s", number)) > 0) {
        *errorCode = pushFront(&list, atoi(number));
        if (errorCode == 1) {
            fclose(file);
            free(number);
            deleteList(&list);
            *errorCode = 1;
            return false;
        }
    }
    fclose(file);
    free(number);
    *errorCode = 0;
    if (checkSymmetric(list)) {
        deleteList(&list);
        return false;
    }
    deleteList(&list);
    return true;
}

BinaryTree *createSortingTree(int *data, int size) {
    BinaryTree *tree = createTree();
    for (int i = 0; i < size; ++i) {
        addElement(data[i], " ", &tree);
    }
    return tree;
}

bool testSort(void) {
    int testData[10] = {0, -19, 77, 25, -16, 9, 45, 82, -100, -4};
    int correctResult[10] = {-100, -19, -16, -4, 0, 9, 25, 45, 77, 82};
    BinaryTree *tree = createSortingTree(testData, 10);
    sortTree(tree, testData, 10);
    for (int i = 0; i < 10; ++i) {
        if (testData[i] != correctResult[i]) {
            clear(&tree);
            return false;
        }
    }
    clear(&tree);
    return true;
}

int main() {
    int errorCode = 0;
    if (!testSymmetric(&errorCode) && errorCode == 0) {
        printf("test have been failed");
        return 1;
    } else if (errorCode == 1) {
        printf("problems :((");
        return 1;
    }
    FILE *file = fopen("../text", "r");
    if (file == NULL) {
        printf("File not found");
        return 1;
    }
    char *number = (char *)malloc(sizeof(char) * 30);
    if (number == NULL) {
        fclose(file);
        return 1;
    }
    List *list = createList();
    while ((fscanf(file, "%s", number)) > 0) {
        pushFront(&list, atoi(number));
    }
    fclose(file);
    free(number);
    bool answer = checkSymmetric(list);
    if (answer) {
        printf("List is symmetric\n");
    } else {
        printf("List isn't symmetric\n");
    }
    deleteList(&list);
    if (!testSort()) {
        return 1;
    }
    int data[5] = {9, 16, -12, 1, 6};
    BinaryTree *tree = createSortingTree(data, 5);
    errorCode = sortTree(tree, data, 5);
    if (errorCode == 1) {
        clear(&tree);
        return 1;
    }
    for (int i = 0; i < 5; ++i) {
        printf("%d%s", data[i], " ");
    }
    clear(&tree);
    return 0;
}
