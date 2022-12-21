#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <stdbool.h>

typedef struct List List;

int getHead(List *list, char *value);

// Create an empty list.
List *createList(int *error);

// Delete a given list with all its elements.
int deleteList(List **list);

int push(List **list, int value, char *word);

void tryAdd(List **list, char *word, bool *isNew, int frequency);

int getSize(List *list);

int pop(List **list);

void delete(char *word, List **list);

void printList(List *list);

int getHeadFrequency(List *list);

int getFrequency(char *word, List *list);

// Print list.
void printList(List *list);

// Check if the given list is empty.
bool isEmpty(List *list);

#endif //LIST_LIST_H
