#include <stdbool.h>
#ifndef STACKMODULE_STACK_H
#define STACKMODULE_STACK_H
typedef struct Node{
    int value;
    struct Node *next;
}Node;

int pushBack(Node **Last, int value);

int pop(Node **head, int *value);

bool isEmpty(Node *head);

int deleteAll(Node **head);

#endif //STACKMODULE_STACK_H
