#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"
#include "test.h"

#define BUFFER_SIZE 30

int main() {
    if (!testCreateTree() || !testAddElement() || !testFind() || !testClear() || !testDeleteElement()) {
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
            int key = 0;
            char value[30] = {0};
            printf("Enter the key and associated value:\n");
            scanf("%d", &key);
            scanf("%s", value);
            addElement(key, value, &tree);
        } else if (option == 1 || option == 2) {
            int key = 0;
            char value[30] = {0};
            bool isExists = false;
            printf("Enter the key\n");
            scanf("%d", &key);
            findValue(key, tree, &isExists, value, BUFFER_SIZE);
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
            int key = 0;
            printf("Enter the key to delete an element\n");
            scanf("%d", &key);
            deleteElement(key, &tree);
        }
        printf("Enter an option\n");
        scanf("%d", &option);
    }
    clear(&tree);
    tree = createTree();
    addElement(3, "3", &tree);
    addElement(2, "2", &tree);
    addElement(1, "1", &tree);
    addElement(4, "4", &tree);
    deleteElement(3, &tree);
    return 0;
}
