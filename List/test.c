#include "test.h"
#include "list.h"
#include <stdbool.h>

#include <stdlib.h>
#include <string.h>

//typedef struct ListElement {
//    int index;
//    int value;
//    struct ListElement *next;
//} ListElement;
//
//typedef struct List {
//    struct ListElement *head;
//    struct ListElement *tail;
//} List;
//
//bool testCreate(void) {
//    List *list = createList();
//    if (isEmpty(list) && (list->head == NULL) && (list->tail == NULL)) {
//        return true;
//    }
//    deleteList(&list);
//    return false;
//}
//
//bool testDelete(void) {
//    List *list = createList();
//    insert(list, 1, 0);
//    insert(&list, 2, 0);
//    deleteList(&list);
//    if (isEmpty(list)) {
//        return true;
//    }
//    return false;
//}
//
//bool testPushBack(void) {
//    List *list = createList();
//    insert(list, 19, 0);
//    if (isEmpty(list) && (list->tail == list->head)) {
//        deleteList(list);
//        return false;
//    }
//    deleteList(list);
//    return true;
//}
//
//bool testPop(void) {
//    List *list = createList();
//    insert(&list, 16);
//    pop(&list);
//    if (!isEmpty(list)) {
//        deleteList(list);
//        return false;
//    }
//    deleteList(list);
//    return true;
//}
//
//bool testIsEmpty(void) {
//    List *list = createList();
//    if (isEmpty(list)) {
//        return true;
//    }
//    deleteList(list);
//    return false;
//}