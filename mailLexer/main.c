#include <stdio.h>
#include "lexer.h"

bool test(void) {
    char *trueSamples[3] = {"ANNA.NIKOLAEVAKONS@GMAIL.C", "AJI%._+-45@AWRT-GHJ.GYSUY-FTY.A", "ABOBUS%ABOBUS@MAIL.MAIL.S"};
    char *falseSamples[3] = {"AHUSIUH@@AFTYTF.R", "@HAUIUH.HUAI@HAUI.X", "GAYUYGS.%GAYUY.GY%567@GAYU654.FTYT"};
    for (int i = 0; i < 3; ++i) {
        if (!isCorrectMail(trueSamples[i])) {
            return false;
        }
        if (isCorrectMail(falseSamples[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    if (!test()) {
        return 1;
    }
    printf("Enter the address to check:\n");
    char string[STR_SIZE] = {0};
    scanf("%s", string);
    if (isCorrectMail(string)) {
        printf("It's a correct mail address");
    } else {
        printf("It's an incorrect mail address");
    }
    return 0;
}
