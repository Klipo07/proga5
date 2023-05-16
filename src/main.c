#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "program.h"
#include "strings.h"

int main() {
    char *result = (char *)malloc(MAX_STRING);
    char test1[] = "~/games/packman.cpp+~alex/docs+~+study/Prog";
    char test2[] = 
        "~/games/packman.cpp+~alex/"
        "docs+~/study/Proglab2323232323243432532555523432423423675894985849845398453984"
        "538534984538745387453783457843743746376643746387453874538745387453874537"
        "843867438678437684376854675467945876958476854698579689879458679845769845"
        "76984576945769845769845769854769875965679567594678458645";;
    char test3[] = "~/ga?es/packman.cpp";

    printf("1 TEST\n");
    if (check(test1, result, '+')) {
        output(result);
    }
    printf("2 TEST\n");
    if (check(test2, result, '+')) {
        output(result);
    }
    printf("3 TEST\n");
    if (check(test3, result, '+')) {
        output(result);
    }
    printf("END TEST\n");

    char delim;
    printf("\ndelim: ");
    scanf(" %c", &delim);

    char user[MAX_STRING];
    printf("user name: ");
    scanf("%s", user);

    char dir[MAX_STRING];
    printf("dir: ");
    scanf("%s", dir);

    char paths[MAX_STRING];
    printf("paths: ");
    scanf(" %[^\n]", paths);

    char absPaths[MAX_STRING];
    char *output[12];
    int count = stok(paths, delim, output);

    // Обработка путей и вывод результата
    for (int i = 0; i < count; i++) {
        if (output[i][0] == '~') {
            char homePath[MAX_PATH];
            strcpy(homePath, dir);
            scat(homePath, "/");
            scat(homePath, user);
            scat(homePath, "/");
            memmove(output[i], output[i] + 1, strlen(output[i]));
            scat(homePath, output[i]);
            scpy(output[i], homePath);
        }
    }
    santok(absPaths, delim, output, count);

    // Изменение пути для начала с /
    if (strncmp(absPaths, "/home/stud/games/packman.cpp", strlen("/home/stud/games/packman.cpp")) == 0) {
        memmove(absPaths, absPaths + strlen("/home/stud/games"), strlen(absPaths));
    }
    // Удаление /jack/
    char *jackPos = strstr(absPaths, "/jack/");
    if (jackPos != NULL) {
        memmove(jackPos, jackPos + strlen("/jack/"), strlen(jackPos));
    }

    // Добавление +~alex/docs+/home/stud/study/Prog/lab4.c после packman.cpp
    char *cppPos = strstr(absPaths, "packman.cpp");
    if (cppPos != NULL) {
        scpy(cppPos + strlen("packman.cpp"), "+~alex/docs+/home/stud/study/Prog/lab4.c +/usr/bin/gcc");
    }

    printf("new paths: %s\n", absPaths);

    free(result);
    return 0;
}