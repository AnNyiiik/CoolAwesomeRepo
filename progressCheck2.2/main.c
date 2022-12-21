#include "../List/list.h"
#include "../List/test.h"

int main() {
    if (!test()) {
        return 1;
    }
    int error = 0;
    List *list = createList(&error);
    if (error == 1) {
        deleteList(&list);
        return 1;
    }
    for (int i = 6; i > 0; --i) {
        error = push(&list, i);
        if (error == 1) {
            deleteList(&list);
            return false;
        }
    }
    error = deleteOddPositions(&list);
    if (error == 1) {
        deleteList(&list);
        return false;
    }
    deleteList(&list);
    return 0;
}
