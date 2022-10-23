#include <stdbool.h>

#ifndef CYCLELIST_CYCLELIST_H
#define CYCLELIST_CYCLELIST_H
typedef struct ListElement ListElement;

typedef struct List List;

List *createList(void);

int pushBack(List **list, int value);

int pop(List **list);

int deleteList(List *list);

void delete(List *list, int place);

int getIndex(List *list);

bool isEmpty(List *list);

#endif //CYCLELIST_CYCLELIST_H
