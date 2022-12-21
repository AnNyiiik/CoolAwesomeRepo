#include "lexer.h"
#include "test.h"

int main() {
    if (!test()) {
        return 1;
    }
    int error = writeCommentsToFile("../output", "../input");
    if (error == 1) {
        return 1;
    }
    return 0;
}
