#include "test.h"
#include "lexer.h"

bool testTrue(void) {
    char *testData[8] = {"10", "10.5", "0.52", "1.52E100",
                          "15.43E+63", "0.5E-43", "156E45", "157E+43", "158E-43"};
    for (int i = 0; i < 8; ++i) {
        bool answer = isRealNumber(testData[i]);
        if (!answer) {
            return false;
        }
    }
    return true;
}

bool testFalse(void) {
    char *testData[11] = {"a", "-5", "1.", "23.E5",
                         "23E", "123E+", "E123", "E+", "E-", ".123", "1E54.48"};
    for (int i = 0; i < 11; ++i) {
        bool answer = isRealNumber(testData[i]);
        if (answer) {
            return false;
        }
    }
    return true;
}