#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <stdbool.h>

typedef struct List List;

//Create an empty list.
List *createList(void);

//Delete List with all its elements.
int deleteList(List **list);

//Add a new element at the head.
int push(List **list, int value);

//Insert a new element into the List by place
int insert(List *list, int place, int value);

//Insert a new element into the List by sorted order according to a value.
int insertByOrder(List *list, int value);

//Delete an element by place.
int delete(List *list, int place);

//Delete an element from the head.
int pop(List **list, int *value);

//Check if the list is empty.
bool isEmpty(List *list);

#endif //LIST_LIST_H
