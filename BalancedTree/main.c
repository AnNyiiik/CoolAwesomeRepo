#include <stdio.h>
#include <stdlib.h>
#include "../BinaryTree/tree.h"
#include "../BinaryTree/test.h"

int main() {
    if (!testCreateTree()) {
        return 1;
    }
    if (!testAddElement()) {
        return 1;
    }
    if (!testFind()) {
        return 1;
    }
    if (!testClear()) {
        return 1;
    }
    if (!testDeleteElement()) {
        return 1;
    }
    int option = 0;
    printf("To add an element enter 0\n"
           "to get value by key enter 1\n"
           "to check if the particular key exists enter 2\n"
           "to delete an element by key enter 3\n"
           "to exit enter 4\n");
    scanf("%d", &option);
    BinaryTree *tree = createTree();
    while (option != 4) {
        if (option == 0) {
            char key[STR_SIZE] = {0};
            char value[STR_SIZE] = {0};
            printf("Enter the key and associated value:\n");
            scanf("%s", key);
            scanf("%s", value);
            addElement(key, value, &tree);
        } else if (option == 1 || option == 2) {
            char key[STR_SIZE] = {0};
            char value[STR_SIZE] = {0};
            bool isExists = false;
            printf("Enter the key\n");
            scanf("%s", key);
            findValue(key, tree, &isExists, value);
            if (isExists) {
                if (option == 1) {
                    printf("%s%s", value, "\n");
                } else {
                    printf("An element exists\n");
                }
            } else {
                printf("There is no such element\n");
            }
        } else if (option == 3) {
            char key[STR_SIZE] = {0};
            printf("Enter the key to delete an element\n");
            scanf("%s", key);
            deleteElement(key, &tree);
        }
        printf("Enter an option\n");
        scanf("%d", &option);
    }
    clear(&tree);
}
