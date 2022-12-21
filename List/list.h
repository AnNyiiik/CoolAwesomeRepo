#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <stdbool.h>

typedef struct List List;

// Create an empty list.
List *createList(int *error);

// Delete a given list with all its elements.
int deleteList(List **list);

// Add a new element to the head od the given list.
int push(List **list, int number, int path);

// Insert a new element according to a value.
int insertByOrder(List *list, int number, int path);

// Delete an element placed on the particular place in the given list.
int delete(List *list, int place);

// Delete an element from the head of the given list.
int pop(List **list, int *number, int *path);

// Search the 1st position of an element by given value.
int getElementPlace(List *list, int number);

// Return the path.
int getPath(List *list, int number);

// Print list.
void printList(List *list);

// Check if the given list is empty.
bool isEmpty(List *list);

#endif //LIST_LIST_H
