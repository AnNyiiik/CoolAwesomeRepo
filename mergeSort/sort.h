#include <stdbool.h>
#ifndef MERGESORT_SORT_H
#define MERGESORT_SORT_H
typedef struct ListElement ListElement;

typedef struct List List;

List *createList(void);

int deleteList(List *list);

int pushBack(List **list, char *name, char *phone);

int pop(List **list);

bool isEmpty(List *list);

ListElement *merge(ListElement *halfFirst, ListElement *halfSecond, int key);

void divide(ListElement *full, ListElement **first, ListElement **second);

void sort(List **list, int key);

void printList(List *list);

#endif //MERGESORT_SORT_H
