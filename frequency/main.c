#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

int countCharacters(int *data, int size, int *reduced) {
    int index = 0;
    for (int i = 0; i < size - 1; ++i) {
        if (data[i] != data[i + 1]) {
            reduced[index] = data[i];
            ++index;
        }
    }
    reduced[index] = data[size - 1];
    ++index;
    return index;
}

bool testTextReduce(void) {
    char *correctAnswer = "aba";
    FILE *file = fopen("../testFile", "r");
    if (file == NULL) {
        printf("%s", "file not found!");
        return 1;
    }
    int data[11] = {0};
    int charactersRead = 0;
    int character = 0;
    while ((character = fgetc(file)) != EOF) {
        data[charactersRead] = character;
        ++charactersRead;
    }
    fclose(file);
    if (charactersRead != 11) {
        return false;
    }
    int *result = (int*) malloc(sizeof(int) * 11);
    if (result == NULL) {
        return false;
    }
    int size = countCharacters(data, charactersRead, result);
    if (size != 3) {
        free(result);
        return false;
    }
    for (int i = 0; i < 3; ++i) {
        if ((int)correctAnswer[i] != result[i]) {
            free(result);
            return false;
        }
    }
    for (int i = 3; i < 10; ++i) {
        if (result[i] != 0) {
            free(result);
            return false;
        }
    }
    free(result);
    return true;
}

int main() {
    //3
    if (!testTextReduce()) {
        return 1;
    }
    setlocale(LC_ALL, "RUS");
    FILE *file = fopen("../text", "r");
    if (file == NULL) {
        printf("%s", "file not found!");
        return 1;
    }
    int data[10000] = {0};
    int charactersRead = 0;
    int character = 0;
    while ((character = fgetc(file)) != EOF) {
        data[charactersRead] = character;
        ++charactersRead;
    }
    fclose(file);
    int *reduced = (int*)malloc(sizeof(int) * 1000);
    if (reduced == NULL) {
        printf("Problems with allocation");
        return 1;
    }
    int size = countCharacters(data, charactersRead, reduced);
    for (int i = 0; i < size; ++i) {
        printf("%c", (char)reduced[i]);
    }
    free(reduced);
    return 0;
}