#ifndef LA_H
#define LA_H

#include <stdio.h>
#define MAX_LEXEME 100

struct token {
    char lexeme[MAX_LEXEME];
    char type[20];
    int row;
    int col;
};

struct token getNextToken(FILE *fp);

#endif

