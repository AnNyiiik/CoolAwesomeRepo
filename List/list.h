#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <stdbool.h>

typedef struct List List;

// Create an empty list.
List *createList(int *error);

// Delete List with all its elements.
int deleteList(List **list);

// Add a new element at the head.
int push(List **list, int value);

// Delete an element from the head.
int pop(List **list, int *value);

// Check if the list is empty.
bool isEmpty(List *list);

// Delete all element with are placed on odd positions.
int deleteOddPositions(List **list);

#endif //LIST_LIST_H
