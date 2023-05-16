#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

#include "program.h"
#include "strings.h"

char *input(char *delim) {
  char *path = (char *)malloc(MAX_STRING);
  printf("delim: ");
  scanf("%c", delim);
  printf("\npath: ");
  scanf("%s", path);
  printf("\n");
  return path;
}

/*\	разделитель подкаталогов
/	ключи командного интерпретатора
:	отделяет букву диска в Windows-путях
*	заменяющий символ (маска «любое количество любых символов»)
?	заменяющий символ (маска «один любой символ»)
«	используется для указания путей, содержащих пробелы
<	обозначение перенаправления ввода
>	обозначение перенаправления вывода
|	обозначение программного конвейера*/
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
            scpy(&result[slen(output[i])], "\n^\nError, path is too long");
            return Error_Length;
        }
        else if (output[i][0] != '~' && output[i][0] != '/') { // Добавлено условие для символа '~'
            scpy(result, output[i]);
            scpy(&result[slen(output[i])], "\n^\nError, expected '/'");
            return Error_String;
        }
    }
    for (size_t i = 0; i < slen(path); i++) {
        if (is_correct_symbol(path[i])) {
            scpy(result, &path[i]);
            scpy(&result[slen(&path[i])], "\n^\nError, unresolved symbol - ':*?«<>|\\'");
            return Error_Symbol;
        }
    }
    santok(path, delim, output, count);
    return 0;
}

/*delim: +
paths:
/cygdrive/c/Windows/system32+/cygdrive/e/Distrib/msoffice.exe+/home/alex/prog/lab4.c
Выход:
new paths: C:\Windows\system32+E:\Distrib\msoffice.exe+/home/alex/prog/lab4.c*/
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