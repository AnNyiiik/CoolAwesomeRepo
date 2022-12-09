#include <stdbool.h>

#ifndef CYCLELIST_CYCLELIST_H
#define CYCLELIST_CYCLELIST_H
typedef struct ListElement ListElement;

typedef struct List List;

List *createList(void);

int pushBack(List **list, int value);

int pop(List **list);

int deleteList(List **list);

void delete(List **list, ListElement **elementBeforeDeleted);

bool isEmpty(List *list);

ListElement *getHead(List *list);

ListElement *getNext(ListElement *element);

int getIndexFirst(List *list);

#endif //CYCLELIST_CYCLELIST_H
