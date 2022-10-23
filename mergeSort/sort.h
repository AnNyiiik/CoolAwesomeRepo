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

#endif //MERGESORT_SORT_H
