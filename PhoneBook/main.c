#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *name;
    char phone[20];
} PhoneList;
int main() {
    setlocale(LC_ALL, "RUS");
    printf("%s%s%s%s%s%s", "Для того, чтобы выйти, введите 0.\n",
                           "Чтобы добавить запись, введите 1.\n",
                 "Чтобы распечатать все имеющиеся записи, введите 2.\n",
                 "Чтобы найти телефон по имени, введите 3.\n",
                 "Чтобы найти имя по телефону, введите 4.\n",
                 "Сохранить текущие данные в файл, введите 5.");
    int commandCode = 0;
    scanf("%d", &commandCode);
    if (commandCode > 5 || commandCode < 0) {
        printf("%s", "Неверный код команды, попробуйте ввести значение еще раз.");
        return 0;
    } if (commandCode == 0) {
        return 0;
    } else if (commandCode == 1) {
        printf("%s", "Введите имя и номер:\n");
        PhoneList dataEntry;
        dataEntry.name = malloc(sizeof(char) * (100));
        scanf("%s%s", dataEntry.name, dataEntry.phone);
        //printf("%s%s%s", dataEntry.name, ", ", dataEntry.phone);
        FILE *file = fopen("/Users/annnikolaeff/CoolAwesomeRepo/PhoneBook/data.txt", "w");
        if (file == NULL) {
            printf("%s", "Файл не найден!");
            return 1;
        }
        fwrite(dataEntry.name, sizeof(char), strlen(dataEntry.name), file);
        fwrite(" ", sizeof(char), 1, file);
        fwrite(dataEntry.phone, sizeof(char), strlen(dataEntry.phone), file);
        fwrite("\n", sizeof(char), 1, file);
        fclose(file);
        free(dataEntry.name);

    } else if (commandCode == 2) {
        FILE *file = fopen("/Users/annnikolaeff/CoolAwesomeRepo/PhoneBook/data.txt", "r");
        if (file == NULL) {
            printf("%s", "Файл не найден!");
            return 1;
        }
        int countWords = 0;
        while (!feof(file)) {
            char *buffer = malloc(sizeof(char) * 200);
            const int readBytes = fscanf(file, "%s", buffer);
            if (readBytes < 0) {
                free(buffer);
                break;
            }
            ++countWords;
            if (countWords % 2) {
                printf("%s%s", buffer, " ");
            } else {
                printf("%s%s", buffer, "\n");
            }
            free(buffer);
        }
        fclose(file);
    }

    return 0;
}

//0 - выйти
//1 - добавить запись (имя и телефон)
//2 - распечатать все имеющиеся записи
//3 - найти телефон по имени
//4 - найти имя по телефону
//5 - сохранить текущие данные в файл
