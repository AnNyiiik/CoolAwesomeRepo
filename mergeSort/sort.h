#ifndef MERGESORT_SORT_H
#define MERGESORT_SORT_H

#include <stdbool.h>
#include "../List/list.h"

//Sort a given list by key (1 - by phone, 0 - by name).
void mergeSort(List **list, int key);

#endif //MERGESORT_SORT_H
