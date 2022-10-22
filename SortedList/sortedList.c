#include "sortedList.h"
#include "../List/list.h"

int insert(List **list, int *value) {
    int errorCode = 0;
    if (isEmpty(list)) {
        errorCode = pop(list, value);
        if (errorCode != 0) {
            return 1;
        }
        return 0;
    }
}