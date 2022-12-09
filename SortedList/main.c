#include <stdio.h>
#include "../List/list.h"
#include "../List/test.h"
int main() {
    if (!testCreate() || !testDelete() || !testInsert() || !testPop() || !testInsertByOrder() || !testIsEmpty()) {
        return 1;
    }
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
            int value = 0;
            printf("%s", "Please, enter the value:\n");
            scanf("%d", &value);
            errorCode = insertByOrder(list, value);
            if (errorCode != 0) {
                return 1;
            }
        } else if (option == 2) {
            int value = 0;
            printf("%s", "Please, enter the value:\n");
            scanf("%d", &value);
            int place = getElementPlace(list, value);
            if (place != -1) {
                delete(list, place);
            }
        } else if (option == 3) {
            printList(list);
        }
        scanf("%d", &option);
        if (option < 0 || option > 3) {
            printf("%s", "There is no such a command. Please, try again.\n");
            return 1;
        }
    }
    int errorCode = deleteList(&list);
    if (errorCode != 0) {
        return 1;
    }
    return 0;
}
//    0 – выйти
//    1 – добавить значение в сортированный список
//    2 – удалить значение из списка
//    3 – распечатать список
//3 5 8 19 -3 6