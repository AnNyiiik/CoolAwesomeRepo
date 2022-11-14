#include <stdbool.h>
#ifndef LIST_LIST_H
#define LIST_LIST_H
typedef struct ListElement ListElement;

typedef struct List List;

List *createList(void);

int deleteList(List **list);

int push(List **list, int value, char *word);

int pop(List **list);

void delete(char *word, List **list);

bool isEmpty(List *list);
#endif //LIST_LIST_H
