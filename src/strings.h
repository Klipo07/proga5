#pragma once

#include <stdint.h>
#include <stdio.h>

size_t slen(const char *str);
int scmp(char *first, char *second);
int sncmp(const char *first, const char *second, size_t count);
char *scpy(char *toHere, const char *fromHere);
size_t sspn(char *s, const char *accept);
int stok(char *s, const char symbol, char *output[]);
char *santok(char *result, const char symbol, char *input[], int count);
char *scat(char *dest, char *src);
size_t find(const char *str, const char *w);
int replace(char *str, const char *old, const char *new);
int replace_all(char *str, char *old, char *new);
char to_upper(char symbol);