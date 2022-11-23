#include <stdio.h>
#include <stdlib.h>
#include "../List/list.h"

int main() {
    FILE *file = fopen("../text", "r");
    if (file == NULL) {
        printf("File not found");
        return 1;
    }
    char *number = (char *)malloc(sizeof(char) * 30);
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
    return 0;
}
