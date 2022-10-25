#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../CycleList/cycleList.h"
#include "../CycleList/test.h"
int whoWillSurvive(int numberOfWarriors, int gap) {
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
    free(list);
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
    if (!testCreate()) {
        printf("Test createList has been failed");
        return 1;
    }
    if (!testPushBack()) {
        printf("Test PushBack has been failed");
        return 1;
    }
    if (!testPop()) {
        printf("Test Pop has been failed");
        return 1;
    }
    if (!testDelete()) {
        printf("Test delete has been failed");
        return 1;
    }
    if (!testIsEmpty()) {
        printf("Test IsEmpty has been failed");
        return 1;
    }
    if (!test()) {
        printf("Algorithm's tests have been failed");
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
