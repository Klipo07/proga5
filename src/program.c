#include <stdio.h>
#include <stdlib.h>

#include "program.h"
#include "strings.h"

char *input(char *delim, char *user, char *dir) {
  char *path = (char *)malloc(MAX_STRING);
  printf("\ndelim: ");
  scanf(" %c", delim);
  printf("user name: ");
  scanf("%s", user);
  printf("dir: ");
  scanf("%s", dir);
  printf("paths: ");
  scanf(" %[^\n]", path);
}

int is_correct_symbol(char symbol) {
    char symbols[] = ":*?«<>|\\";
    for (size_t i = 0; i < slen(symbols); i++) {
      if (symbols[i] == symbol)
        return 1;
    }
    return 0;
}

int check(char *path, char *result, char delim) {
    char *output[12];
    int count = stok(path, delim, output);

    for (int i = 0; i < count; i++) {
        if (slen(output[i]) > MAX_PATH) {
            scpy(result, output[i]);
            scpy(&result[slen(output[i])], "\n^\nError: Path is too long.");
            return 1;
        }
        else if (output[i][0] != '~') {
            scpy(result, output[i]);
            scpy(&result[slen(output[i])], "\n^\nError: Expected '~'");
            return 1;
        }
    }
    
    for (int i = 0; i < count; i++) {
        for (size_t j = 0; j < slen(output[i]); j++) {
            if (is_correct_symbol(output[i][j])) {
                scpy(result, output[i]);
                scpy(&result[slen(output[i])], "\n^\nError: Unresolved symbol - ':*?«<>|\\'");
                return 1;
            }
        }
    }

    santok(path, delim, output, count);
    return 0;
}

char *process(char *path, const char delim) {
    char *result = (char *)malloc(MAX_STRING);
    char *output[12];
    int count = stok(path, delim, output);
    for (int i = 0; i < count; i++) {
      if (output[i][0] == '~') {
        // Получаем домашний каталог текущего пользователя
        const char *home = getenv("HOME");
        if (home != NULL) {
          // Заменяем символ '~' на домашний каталог
          replace(output[i], "~/", (const char *)home);
        }
      }
    }
    return santok(result, delim, output, count);
}

void output(char *path) { printf("%s\n\n", path); }