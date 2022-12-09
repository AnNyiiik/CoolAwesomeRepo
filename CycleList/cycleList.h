#ifndef CYCLELIST_CYCLELIST_H
#define CYCLELIST_CYCLELIST_H

#include <stdbool.h>

typedef struct List List;

//Create an empty List.
List *createList(void);

//Add a new element to the tail of the given list.
int pushBack(List **list, int value);

//Delete an element from a head of the given list.
int pop(List **list);

//Delete a given list and all its elements.
int deleteList(List *list);

//Delete an element from the list by place.
void delete(List *list, int place);

//Return an index.
int getIndex(List *list);

//Check if the list is empty.
bool isEmpty(List *list);

#endif //CYCLELIST_CYCLELIST_H
