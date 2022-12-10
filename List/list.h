#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <stdbool.h>

typedef struct List List;

//Create an empty list.
List *createList(void);

//Delete a list with all its elements.
int deleteList(List **list);

//Add a new element to the end of the list.
int pushBack(List **list, char *name, char *phone);

//Delete an element from the head of the list.
int pop(List **list);

//Check if the list is empty.
bool isEmpty(List *list);

//Check if there is only one element in list.
bool isOneElementSize(List *list);

//Divide List into two parts.
void divide(List *full, List **first, List **second);

//Compare heads of two given lists by name.
bool isLessFirst(List *headFirst, List *headSecond, int key);

//Return head's name value.
char *getHeadName(List *list);

//Return head's phone value.
char *getHeadPhone(List *list);

//Return tail's name value.
char *getTailName(List *list);

//Return tail's phone value.
char *getTailPhone(List *list);

//Print list.
void printList(List *list);

//Check if the lists are equal.
bool isEqualLists(List *first, List *second);
#endif //LIST_LIST_H
