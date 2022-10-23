#include <stdio.h>
#include <stdlib.h>
#include "../CycleList/cycleList.h"
int main() {
    printf("Enter the number of warriors:\n");
    int numberOfWarriors = 0;
    scanf("%d", &numberOfWarriors);
    printf("Enter the gap between them:\n");
    int gap = 0;
    scanf("%d", &gap);
    List *list = createList();
    for (int i = 0; i < numberOfWarriors; ++i) {
        pushBack(&list, 1);
    }
    int index = 0;
    int answer = 1;
    while (!isEmpty(list)) {
        index = (index + gap - 1) % numberOfWarriors;
        delete(list, index);
        --numberOfWarriors;
        if (!isEmpty(list)) {
            answer = getIndex(list);
        }
    }
    printf("%d", answer);
    free(list);
    return 0;
}
