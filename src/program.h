#pragma once

#define MAX_LENGTH 100
#define MAX_TOKENS 10
#define ALLOWED_CHARS "+/~abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.:"
#define NO_ERROR 0
#define ERROR_LENGTH -1

void input(char *delim, char *dir, char *paths);
int check(const char *str);
void process(char delim, const char *dir, char *paths);
void output(const char *paths);
