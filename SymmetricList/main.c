#include <stdio.h>
#include <stdlib.h>
#include "../List/list.h"
#include "../BinaryTree/tree.h"

bool testSymmetric(void) {
    FILE *file = fopen("../testFile", "r");
    if (file == NULL) {
        return false;
    }
    char *number = (char *)malloc(sizeof(char) * 30);
    if (number == NULL) {
        fclose(file);
        return 1;
    }
    List *list = createList();
    while ((fscanf(file, "%s", number)) > 0) {
        int errorCode = pushFront(&list, atoi(number));
        if (errorCode == 1) {
            fclose(file);
            deleteList(&list);
            return 1;
        }
    }
    fclose(file);
    free(number);
    if (checkSymmetric(list)) {
        return false;
    }
    return true;
}

void sortingTree(int *data, int size) {
    BinaryTree *tree = createTree();
    for (int i = 0; i < size; ++i) {
        addElement(data[i], " ", &tree);
    }
}

int main() {
    if (!testSymmetric()) {
        return 1;
    }
    FILE *file = fopen("../text", "r");
    if (file == NULL) {
        printf("File not found");
        return 1;
    }
    char *number = (char *)malloc(sizeof(char) * 30);
    if (number == NULL) {
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
        printf("List is symmetric");
    } else {
        printf("List isn't symmetric");
    }
    deleteList(&list);
    int *data[5] = {9, 16, -12, 1, 0};
    sortingTree(data, 5);
    return 0;
}
