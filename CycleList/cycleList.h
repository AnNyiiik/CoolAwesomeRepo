#ifndef CYCLELIST_CYCLELIST_H
#define CYCLELIST_CYCLELIST_H

#include <stdbool.h>

typedef struct ListElement ListElement;

typedef struct List List;

//Create an empty List.
List *createList(void);

//Add a new element to the tail of the given list.
int pushBack(List **list, int value);

//Delete an element from a head of the given list.
int pop(List **list);

//Delete a given list and all its elements.
int deleteList(List **list);

//Delete an element from the list by pointer.
void delete(List **list, ListElement **elementBeforeDeleted);

//Check if the list is empty.
bool isEmpty(List *list);

//Return head element pointer.
ListElement *getHead(List *list);

//Return next after given element pointer.
ListElement *getNext(ListElement *element);

//Return index of the head element.
int getIndexFirst(List *list);

#endif //CYCLELIST_CYCLELIST_H
