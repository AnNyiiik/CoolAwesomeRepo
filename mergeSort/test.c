#include "test.h"
#include "sort.h"

bool testSort(void) {
    List *listCorrectSequence = createList();
    pushBack(&listCorrectSequence, "B", "8906");
    pushBack(&listCorrectSequence, "G", "9018");
    pushBack(&listCorrectSequence, "W", "7896");
    List *list = createList();
    pushBack(&list, "W", "7896");
    pushBack(&list, "B", "8906");
    pushBack(&list, "G", "9018");
    mergeSort(&list, 0);
    if (!isEqualLists(list, listCorrectSequence)) {
        deleteList(&list);
        deleteList(&listCorrectSequence);
        return false;
    }
    deleteList(&list);
    deleteList(&listCorrectSequence);
    list = createList();
    listCorrectSequence = createList();
    pushBack(&list, "G", "9018");
    pushBack(&list, "W", "7896");
    pushBack(&list, "B", "8906");
    pushBack(&listCorrectSequence, "W", "7896");
    pushBack(&listCorrectSequence, "B", "8906");
    pushBack(&listCorrectSequence, "G", "9018");
    mergeSort(&list, 1);
    if (!isEqualLists(list, listCorrectSequence)) {
        deleteList(&list);
        deleteList(&listCorrectSequence);
        return false;
    }
    deleteList(&list);
    deleteList(&listCorrectSequence);
    return true;
}

