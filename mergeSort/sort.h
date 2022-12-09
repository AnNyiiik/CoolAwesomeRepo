#ifndef MERGESORT_SORT_H
#define MERGESORT_SORT_H

#include <stdbool.h>

typedef struct List List;

//Create an empty list.
List *createList(void);

//Delete a list with all its elements.
int deleteList(List *list);

//Add a new element to the end of the list.
int pushBack(List **list, char *name, char *phone);

//Delete an element from the head of the list.
int pop(List **list);

//Check if the list is empty.
bool isEmpty(List *list);

//Sort a given list by key (1 - by phone, 0 - by name).
void sort(List **list, int key);

//Print list.
void printList(List *list);

#endif //MERGESORT_SORT_H
