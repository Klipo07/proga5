#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "program.h"

//Функция вычисления длины строки
size_t slen(const char *str) {
  size_t size = 0;
  while (str[size] != '\0') {
    size++;
  }
  return size;
}

//Функция сравнения строк
int scmp(char *first, char *second) {
  while (*first != '\0' || *second != '\0') {
    if (*first > *second)
      return 1;
    if (*first < *second)
      return -1;
    first++;
    second++;
  }
  return 0;
}

int sncmp(const char *first, const char *second, size_t count) {
  while ((*first != '\0' || *second != '\0') && count) {
    if (*first > *second)
      return 1;
    if (*first < *second)
      return -1;
    first++;
    second++;
    count--;
  }
  return 0;
}

//Функция копирования строк
char *scpy(char *toHere, const char *fromHere) {
  for (size_t i = 0; i <= slen(fromHere); i++) {
    toHere[i] = fromHere[i];
  }
  return toHere;
}

int is_symbol(char s1, const char *accept) {
  while (*accept != '\0') {
    if (s1 == *accept)
      return 1;
    accept++;
  }
  return 0;
}

//Функция проверки символа на принадлежность заданному множеству
size_t sspn(char *s, const char *accept) {
  size_t size = 0;
  size_t counter = 0;
  while (*s != '\0') {
    if (is_symbol(*s, accept))
      counter++;
    else
      counter = 0;
    size = size > counter ? size : counter;
    s++;
  }
  return size;
}

//Функция разбиения строки на токены разделенные заданным символом
int stok(char *s, const char symbol, char *output[]) {
  int count = 0;
  output[count++] = s;
  size_t size = slen(s);
  for (size_t i = 0; i < size; i++) {
    if (s[i] == symbol) {
      s[i] = '\0';
      output[count++] = &s[i + 1];
    }
  }
  return count;
}

char *scat(char *dest, char *src) {
  scpy(&dest[slen(dest)], src);
  return dest;
}

char *santok(char *result, const char symbol, char *input[], int count) {
  size_t len = 0;
  for (int i = 0; i < count; i++) {
    scpy(&result[len], input[i]);
    len = slen(result);
    result[len++] = symbol;
  }
  result[--len] = '\0';
  return result;
}

size_t find(const char *str, const char *w) {
  size_t len = slen(str);
  size_t w_len = slen(w);
  if (w_len > len)
    return len;
  for (size_t id = 0; id < len - w_len; id++) {
    if (sncmp(str + id, w, w_len) == 0)
      return id;
  }
  return len;
}

int replace(char *str, const char *old, const char *new) {
  size_t id = find(str, old);
  size_t end_id = slen(str) - slen(old) + slen(new);
  if (id == slen(str))
    return 1;

  char *str_p = (str + id + slen(old));
  char *tmp = (char *)malloc(slen(str_p));
  scpy(tmp, str_p);
  scpy(str + id, (char *)new);
  scpy(str + id + slen(new), tmp);
  free(tmp);
  str[end_id] = '\0';
  return 0;
}

char to_upper(char symbol) {
  if (symbol >= 'a' && symbol <= 'z')
    symbol -= 'a' - 'A';
  return symbol;
}

int replace_all(char *str, char *old, char *new) {
  int count = 0;
  while (!replace(str, old, new)) {
    count++;
  }
  return count;
}