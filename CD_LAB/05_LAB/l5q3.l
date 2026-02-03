%{
#include <stdio.h>

int posIntCount = 0;
int negIntCount = 0;
int posFloatCount = 0;
int negFloatCount = 0;
%}

%%
-[0-9]+\.[0-9]+     { negFloatCount++; }
[0-9]+\.[0-9]+      { posFloatCount++; }
-[0-9]+             { negIntCount++; }
[0-9]+              { posIntCount++; }
[ \t\n]             { }
.                   { }
%%

int main()
{
    yylex();

    printf("Positive Integers: %d\n", posIntCount);
    printf("Negative Integers: %d\n", negIntCount);
    printf("Positive Floating Numbers: %d\n", posFloatCount);
    printf("Negative Floating Numbers: %d\n", negFloatCount);

    return 0;
}

int yywrap()
{
    return 1;
}
