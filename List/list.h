#include <stdbool.h>
#ifndef LIST_LIST_H
#define LIST_LIST_H

typedef struct List List;

int getHead(List *list, char *value);

List *createList(int *error);

int deleteList(List **list);

int push(List **list, int value, char *word);

void tryAdd(List **list, char *word, bool *isNew, int frequency);

int getSize(List *list);

int pop(List **list);

void delete(char *word, List **list);

void printList(List *list);

int getHeadFrequency(List *list);

int getFrequency(char *word, List *list);

bool isEmpty(List *list);
#endif //LIST_LIST_H
