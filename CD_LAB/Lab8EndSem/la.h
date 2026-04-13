#ifndef LA_H
#define LA_H

#include <stdio.h>

struct token {
    char lexeme[100];
    char type[20];
    int row;
    int col;
};

struct token getNextToken(FILE *fp);

#endif

