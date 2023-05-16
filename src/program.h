#pragma once
#define MAX_PATH 260
#define MAX_STRING 4096

enum errors {
  Error_Length = 1,
  Error_Symbol,
  Error_String,
};


char *input(char *delim, char *user, char *dir);
int check(char *path, char *result, char delim);
char *process(char *path, const char delim);
void output(char *path);