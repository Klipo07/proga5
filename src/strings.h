#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int slen(const char *str);
char *stok(char *str, char delim, char **context, int maxTokens);
int sspn(const char *str, const char *charset);
int scmp(const char *str1, const char *str2);
void scpy(const char *src, char *dest);