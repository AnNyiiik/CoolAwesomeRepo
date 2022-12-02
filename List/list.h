#include <stdbool.h>
#ifndef LIST_LIST_H
#define LIST_LIST_H
typedef struct ListElement ListElement;

typedef struct List List;

List *createList(void);

int deleteList(List **list);

int push(List **list, int number, int path);

int insert(List *list, int place, int number, int path);

int insertByOrder(List *list, int number, int path);

int delete(List *list, int place);

int pop(List **list, int *number, int *path);

int getElementPlace(List *list, int number);

int getPath(List *list, int number);

void printList(List *list);

bool isEmpty(List *list);
#endif //LIST_LIST_H
