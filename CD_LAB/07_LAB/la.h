#ifndef LA_H
#define LA_H

#include <stdio.h>
#define MAX_LEXEME 100
#define MAX_TYPE 30

struct token {
    char lexeme[MAX_LEXEME];
    char type[MAX_TYPE];
    int row;
    int col;
};

struct token getNextToken(FILE *fp);

#endif

