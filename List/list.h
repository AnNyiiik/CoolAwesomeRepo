#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <stdbool.h>

typedef struct List List;

//Create an empty list.
List *createList(void);

//Delete List with all its elements.
int deleteList(List **list);

//Add a new element at the head.
int pushBack(List **list, int value);

//Delete an element from the head.
int pop(List **list, int *value);

//Check if the list is empty.
bool isEmpty(List *list);

//Print to file.
void printList(List *list, char const *path);

//Concatenate two given lists.
List *makeOne(List *listFirst, List *listSecond);

#endif //LIST_LIST_H
