#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STR_SIZE 100

int readFromFile(const char *pathInput, const char *pathOutput) {
    FILE *input = fopen(pathInput, "r");
    if (input == NULL) {
        return 1;
    }
    FILE *output = fopen(pathOutput, "w");
    if (output == NULL) {
        fclose(input);
        return 1;
    }
    bool isOpened = false;
    char string[STR_SIZE] = {0};
    int character = 0;
    int position = 0;
    while ((character = fgetc(input)) > 0 && position < STR_SIZE) {
        if (character == '"' && !isOpened) {
            string[0] = '"';
            isOpened = true;
            position = 1;
        } else if (isOpened) {
            string[position] = (char)character;
            ++position;
            if (character == '"') {
                isOpened = false;
                fprintf(output, "%s\n", string);
                memset(string, '\0', sizeof(char) * STR_SIZE);
            }
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}

bool test(void) {
    char *correctAnswers[6] = {"\"jaiosiaj\"", "\"jaisoi3029c\"", "\"jaisoij\"",
                               "\"asoaj\"", "\"jaisoiaj\"", "\"\""};
    int error = readFromFile("../testData", "../output");
    if (error == 1) {
        return false;
    }
    FILE *file = fopen("../output", "r");
    if (file == NULL) {
        return false;
    }
    char string[STR_SIZE] = {0};
    int readLines = 0;
    while (fscanf(file, "%s", string) > 0) {
        if (strcmp(correctAnswers[readLines], string) != 0) {
            fclose(file);
            return false;
        }
        ++readLines;
    }
    fclose(file);
    return readLines == 6;
}

int main() {
    if (!test()) {
        printf("test has been failed");
        return 1;
    }
    int error = readFromFile("../input", "../output");
    return error;
}
