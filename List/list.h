#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <stdbool.h>

typedef struct List List;

//Create an empty list.
List *createList(int *error);

//Delete List with all its elements.
int deleteList(List **list);

//Add a new element at the tail.
int pushBack(List **list, char const *value);

//Delete an element from the head.
int pop(List **list, char *value);

//Check if the list is empty.
bool isEmpty(List *list);

//Convert list to array.
int getArray(List *list, char **array, int size);

//Search and add all values that are in the list and start with "a".
int addStringsStartsWithA(List **list);

//Return a size of the list.
int getSize(List *list);

#endif //LIST_LIST_H
