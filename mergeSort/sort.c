#include "sort.h"
#include <string.h>

List *merge(List *halfFirst, List *halfSecond, int key) {
    if (isEmpty(halfFirst)) {
        return halfSecond;
    }
    else if (isEmpty(halfSecond)) {
        return halfFirst;
    }
    List *result = createList();
    while (!isEmpty(halfFirst) && !isEmpty(halfSecond)) {
        if (isLessFirst(halfFirst, halfSecond, key)) {
            pushBack(&result, getHeadName(halfFirst), getHeadPhone(halfFirst));
            pop(&halfFirst);
        } else {
            pushBack(&result, getHeadName(halfSecond), getHeadPhone(halfSecond));
            pop(&halfSecond);
        }
    }
    if (isEmpty(halfFirst)) {
        while(!isEmpty(halfSecond)) {
            pushBack(&result, getHeadName(halfSecond), getHeadPhone(halfSecond));
            pop(&halfSecond);
        }
    } else {
        while(!isEmpty(halfFirst)) {
            pushBack(&result, getHeadName(halfFirst), getHeadPhone(halfFirst));
            pop(&halfFirst);
        }
    }
    return result;
}

void mergeSort(List **head, int key) {
    if (*head == NULL || isEmpty(*head) || isOneElementSize(*head)) {
        return;
    }
    List *firstHalf = NULL;
    List *secondHalf = NULL;
    divide(*head, &firstHalf, &secondHalf);
    mergeSort(&firstHalf, key);
    mergeSort(&secondHalf, key);
    List *list = merge(firstHalf, secondHalf, key);
    *head = list;
}


//if (compare <= 0) {
//result = halfFirst;
//result->next = merge(halfFirst->next, halfSecond, key);
//} else {
//result = halfSecond;
//result->next = merge(halfFirst, halfSecond->next, key);
//}






