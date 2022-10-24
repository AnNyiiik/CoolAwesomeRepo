#include "test.h"
#include "sort.h"
bool testCreate(void) {
    List *list = createList();
    if (isEmpty(list)) {
        return true;
    }
    deleteList(list);
    return false;
}

bool testDelete(void) {
    List *list = createList();
    pushBack(&list, "A", "456");
    pushBack(&list, "N", "407");
    deleteList(list);
    if (isEmpty(list)) {
        return true;
    }
    return false;
}

bool testPushBack(void) {
    List *list = createList();
    pushBack(&list, "A", "456");
    if (isEmpty(list)) {
        deleteList(list);
        return false;
    }
    deleteList(list);
    return true;
}

bool testPop(void) {
    List *list = createList();
    pushBack(&list, "A", "456");
    pop(&list);
    if (!isEmpty(list)) {
        deleteList(list);
        return false;
    }
    return true;
}

bool testIsEmpty(void);


bool testMerge(void);

bool testDivide(void);

bool testSort(void);