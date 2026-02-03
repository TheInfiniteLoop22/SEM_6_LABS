%{
#include <stdio.h>

int vowelTotal = 0;
int consonantTotal = 0;
%}

%%
[aeiouAEIOU]                    { vowelTotal++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] { consonantTotal++; }
.|\n                            { }
%%

int main()
{
    yylex();
    printf("Number of vowels: %d\n", vowelTotal);
    printf("Number of consonants: %d\n", consonantTotal);
    return 0;
}

int yywrap()
{
    return 1;
}

