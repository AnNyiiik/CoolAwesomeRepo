#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "countingSort.h"

int main() {
    if (!(test())) {
        printf("%s", "Tests have been failed\n");
        return 1;
    }
    printf("%s", "Tests have been passed successfully\n");
    FILE *file = fopen("/Users/annnikolaeff/CoolAwesomeRepo/ModuleSort/sourceData", "r");
    int answer = mostFrequentElement(file);
    fclose(file);
    printf("%s%d", "The most frequent element is ", answer);
    return 0;
}
