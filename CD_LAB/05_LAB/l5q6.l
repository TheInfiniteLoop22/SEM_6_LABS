%{
#include <stdio.h>
#include <ctype.h>
%}

%x CMT

%%
"//".*                 { printf("%s", yytext); }

"/*"                   { BEGIN(CMT); printf("%s", yytext); }

<CMT>"*/"              { BEGIN(INITIAL); printf("%s", yytext); }

<CMT>.|\n              { printf("%s", yytext); }

[A-Z]                  { putchar(tolower(yytext[0])); }

.|\n                   { printf("%s", yytext); }
%%

int main(int argc, char *argv[])
{
    if(argc > 1)
        yyin = fopen(argv[1], "r");

    yylex();

    return 0;
}

int yywrap()
{
    return 1;
}

