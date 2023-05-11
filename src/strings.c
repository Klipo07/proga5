#include "strings.h"

// Функция вычисления длины строки
int slen(const char *str) {
    int length = 0;
    
    while (str[length] != '\0') {
        length++;
    }
    
    return length;
}

// Функция разбиения строки на элементы-токены
char *stok(char *str, char delim, char **context, int maxTokens) {
    if (str == NULL) {
        str = *context;
    }
    
    while (*str != '\0' && *str == delim) {
        str++;
    }
    
    if (*str == '\0') {
        return NULL;
    }
    
    char *token = str;
    
    while (*str != '\0' && *str != delim) {
        str++;
    }
    
    if (*str != '\0') {
        *str = '\0';
        *context = str + 1;
    } else {
        *context = str;
    }
    
    return token;
}

// Функция проверки символа на принадлежность заданному множеству символов
int sspn(const char *str, const char *charset) {
    for (int i = 0; charset[i] != '\0'; i++) {
        if (*str == charset[i]) {
            return 1;
        }
    }
    
    return 0;
}

// Функция сравнения строк
int scmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }
    
    return (*str1 - *str2);
}

// Функция копирования строк
void scpy(const char *src, char *dest) {
    while (*src != '\0') {
        *dest = *src;
        src++;
        dest++;
    }
    
    *dest = '\0';
}