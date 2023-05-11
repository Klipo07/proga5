#include "strings.h"
#include "program.h"

// Функция ввода данных
void input(char *delim, char *dir, char *paths) {
    printf("Введите разделитель: ");
    scanf(" %c", delim);
    
    printf("Введите имя каталога: ");
    scanf(" %s", dir);
    
    printf("Введите пути: ");
    scanf(" %[^\n]", paths);
}

// Функция проверки корректности данных
int check(const char *str) {
    int length = slen(str);
    
    // Проверка длины входной строки
    if (length > MAX_LENGTH) {
        return ERROR_LENGTH;
    }
    
    // Проверка символов во входной строке
    for (int i = 0; i < length; i++) {
        if (!sspn(&str[i], ALLOWED_CHARS)) {
            return i;
        }
    }
    
    return NO_ERROR;
}

// Функция обработки данных
void process(char delim, const char *dir, char *paths) {
    char *token;
    char *path = paths;
    
    while ((token = stok(path, delim, &path, MAX_TOKENS)) != NULL) {
        if (token[0] == '~') {
            char absolutePath[MAX_LENGTH];
            scpy(dir, absolutePath);
            scpy(&token[1], &absolutePath[slen(dir)]);
            printf("%s%c", absolutePath, delim);
        } else {
            printf("%s%c", token, delim);
        }
    }
}

// Функция вывода данных
void output(const char *paths) {
    printf("new paths: %s\n", paths);
}

int main() {
    char delim;
    char dir[MAX_LENGTH];
    char paths[MAX_LENGTH];
    
    input(&delim, dir, paths);
    
    int errorPos = check(paths);
    
    if (errorPos == NO_ERROR) {
        process(delim, dir, paths);
        output(paths);
    } else {
        printf("Ошибка: недопустимый символ в позиции %d\n", errorPos);
    }
    
    return 0;
}