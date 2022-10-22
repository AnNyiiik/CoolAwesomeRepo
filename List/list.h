#include <stdbool.h>
#ifndef LIST_LIST_H
#define LIST_LIST_H
typedef struct ListElement ListElement;

typedef struct List List;

List *createList(void);

int deleteList(List **list);

int push(List **list, int value);

int insert(List *list, int place, int value);

int insertByOrder(List *list, int value);

void delete(List *list, int place);

int pop(List **list, int *value);

bool isEmpty(List *list);
#endif //LIST_LIST_H
