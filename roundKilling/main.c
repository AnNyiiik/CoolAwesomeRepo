#include <stdio.h>
#include <stdbool.h>
#include "../CycleList/cycleList.h"
#include "../CycleList/test.h"

int whoWillSurvive(int numberOfWarriors, int gap) {
    List *list = createList();
    for (int i = 0; i < numberOfWarriors; ++i) {
        pushBack(&list, 1);
    }
    ListElement *current = getHead(list);
    int answer = getIndexFirst(list);
    while (!isEmpty(list)) {
        for (int i = 1; i < gap - 1; ++i) {
            current = getNext(current);
        }
        answer = getIndexFirst(list);
        delete(&list, &current);
        current = getNext(current);
    }
    deleteList(&list);
    return answer;
}

bool test(void) {
    int sequenceOfNumberOfPeople[3] = {5, 8, 7};
    int sequenceOfGap[3] = {3, 5, 9};
    int correctAnswers[3] = {4, 3, 7};
    for (int i = 0; i < 3; ++i) {
        int answer = whoWillSurvive(sequenceOfNumberOfPeople[i], sequenceOfGap[i]);
        if (answer != correctAnswers[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    if (!testCreate() || !testPushBack() || !testPop() || !testDelete() || !testIsEmpty() || !test()) {
        printf("Tests have been failed");
        return 1;
    }
    printf("Enter the number of warriors:\n");
    int numberOfWarriors = 0;
    scanf("%d", &numberOfWarriors);
    printf("Enter the gap between them:\n");
    int gap = 0;
    scanf("%d", &gap);
    int answer = whoWillSurvive(numberOfWarriors, gap);
    printf("%d", answer);
    return 0;
}
