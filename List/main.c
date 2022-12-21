#include "list.h"
#include "test.h"
int main() {
    if (!testCreate() || !testDelete() || !testInsert() || !testPop() || !testIsEmpty() || !testInsertByOrder()) {
        return 1;
    }
    List *list = createList();
    push(&list, 12);
    push(&list, 13);
    push(&list, 16);
    insertByOrder(list, 17);
    deleteList(&list);
    return 0;
}
