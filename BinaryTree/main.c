#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"
#include "test.h"

int main() {
    BinaryTree *tree = createTree();
    addElement(2, "abab", &tree);
    addElement(1, "dwe", &tree);
    addElement(6, "fru", &tree);
    addElement(4, "akoap", &tree);
    addElement(7, "appwp", &tree);
    addElement(5, "ajpqo", &tree);
//    if (!testCreateTree()) {
//        return 1;
//    }
//    if (!testAddElement()) {
//        return 1;
//    }
//    if (!testFind()) {
//        return 1;
//    }
//    if (!testClear()) {
//        return 1;
//    }
//    if (!testDeleteElement()) {
//        return 1;
//    }
//    int option = 0;
//    printf("To add an element enter 0\nto get value by key enter 1\nto check if the particular key exists enter 2\nto delete an element by key enter 3\nto exit enter 4\n");
//    scanf("%d", &option);
//    BinaryTree *tree = createTree();
//    while (option != 4) {
//        if (option == 0) {
//            int key = 0;
//            char *value = (char *) malloc(sizeof(char) * 30);
//            printf("Enter the key and associated value:\n");
//            scanf("%d", &key);
//            scanf("%s", value);
//            addElement(key, value, &tree);
//            free(value);
//        } else if (option == 1 || option == 2) {
//            int key = 0;
//            char *value = (char *) malloc(sizeof(char) * 30);
//            bool isExists = false;
//            printf("Enter the key\n");
//            scanf("%d", &key);
//            findValue(key, tree, &isExists, value);
//            if (isExists) {
//                if (option == 1) {
//                    printf("%s%s", value, "\n");
//                } else {
//                    printf("An element exists\n");
//                }
//            } else {
//                printf("There is no such element\n");
//            }
//            free(value);
//        } else if (option == 3) {
//            int key = 0;
//            printf("Enter the key to delete an element\n");
//            scanf("%d", &key);
//            deleteElement(key, &tree);
//        }
//        printf("Enter an option\n");
//        scanf("%d", &option);
//    }
//    clear(&tree);
    return 0;
}
