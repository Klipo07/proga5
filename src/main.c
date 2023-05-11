#include <stdio.h>
#include "strings.h"
#include "program.h"

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