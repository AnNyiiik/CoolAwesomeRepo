#include <stdio.h>
#include "../List/list.h"
int main() {
    int option = 0;
    printf("%s", "Please, enter the option number:\n");
    scanf("%d", &option);
    if (option < 0 || option > 3) {
        printf("%s", "There is no such a command. Please, try again.\n");
        return 1;
    }
    List *list = createList();
    while (option != 0) {
        int errorCode = 0;
        if (option == 1) {

        } else if (option == 2) {
            int value = 0;
            printf("%s", "Please, enter the value:\n");
            scanf("%d", &value);
            errorCode = pop(&list, &value);
            if (errorCode != 0) {
                deleteList(&list);
                printf("%s", "Problems with pop\n");
                return 1;
            }
        } else if (option == 3) {

        }
        scanf("%d", &option);
        if (option < 0 || option > 3) {
            printf("%s", "There is no such a command. Please, try again.\n");
            return 1;
        }
    }
    return 0;
}
//    0 – выйти
//    1 – добавить значение в сортированный список
//    2 – удалить значение из списка
//    3 – распечатать список