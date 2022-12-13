#include <stdio.h>
#include <stdlib.h>

int main() {
    int matrix[5][5] = {0, 1, 0, 1, 0,
                        1, 1, 0, 1, 1,
                        0, 0, 0, 0, 1,
                        1, 1, 0, 0, 0,
                        0, 1, 1, 0, 0};
    system("touch file.dot");
    FILE *file = fopen("../file.dot", "w");
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = i; j < 5; ++j) {
            if (matrix[i][j] == 1) {
                ++count;
            }
        }
    }
    fprintf(file, "graph Matrix {\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = i; j < 5; ++j) {
            if (matrix[i][j] == 1) {
                fprintf(file, " %d -- %d\n", i, j);
            }
        }
    }
    fprintf(file, "}");
    fclose(file);
    system("dot -Tpng file.dot -o image.png");
    system("open ../image.png");
    printf("Hello, World!\n");
    return 0;
}
